#include <stdio.h>
#include <string.h>

#include "city.h"
#include "common.h"
#include "List.h"
#include "map.h"
#include "string_ext.h"
#include "vertex.h"

void printError(status code)
{
    printf("Run time error: %s\n", message(code));
}

void printErrorUnknownName()
{
    printf("We can't find the entered name(s) in our database\n");
}

void printInstruction(List *map)
{
    printf("Route searching is limited to the below list: \n");
    displayList(map);
}

void getCityname(int argc, char const *argv[], char *startCityName, char *goalCityName)
{
    if (argc == 3)
    {
        snprintf((char *)startCityName, MAX_CITY_NAME_LENGTH, "%s", argv[1]);
        snprintf((char *)goalCityName, MAX_CITY_NAME_LENGTH, "%s", argv[2]);
        return;
    }

    printf("Searching for route between 2 cities.\n");

    printf(" - Enter the name of city 1: ");
    // Only get MAX_CITY_NAME_LENGTH from the keyboard
    fgets(startCityName, MAX_CITY_NAME_LENGTH, stdin);
    // fgets also get newline character into end of the string. Need to remove it
    startCityName[strcspn(startCityName, "\n")] = 0;

    printf(" - Enter the name of city 2: ");
    fgets(goalCityName, MAX_CITY_NAME_LENGTH, stdin);
    goalCityName[strcspn(goalCityName, "\n")] = 0;
}

int isValidNames(List *map, City **startCity, char *startCityName, City **goalCity, char *goalCityName)
{
    *startCity = getCityByName(map, startCityName);
    *goalCity = getCityByName(map, goalCityName);

    if (!*startCity || !*goalCity)
    {
        return 0;
    }

    return -1;
}

status initVariables(List **map, List **route)
{
    *map = newList(compareCityByName, printCityInfo);
    if (!(*map))
    {
        return ERRALLOC;
    }

    *route = newList(LIFO, printVertex);
    if (!(*route))
    {
        free(map);
        return ERRALLOC;
    }

    return OK;
}

void delVariables(List *map, List *route)
{
    forEach(route, delVertex);
    delList(route);

    forEach(map, delCity);
    delList(map);
}

int main(int argc, char const *argv[])
{
    status exitCode;
    char startCityName[MAX_CITY_NAME_LENGTH];
    char goalCityName[MAX_CITY_NAME_LENGTH];

    // Get city names
    getCityname(argc, argv, (char *)startCityName, (char *)goalCityName);

    // Initiate the map and vertex list
    List *map, *route;
    exitCode = initVariables(&map, &route);
    if (exitCode != OK)
    {
        printError(exitCode);
        return exitCode;
    }

    // Read data to the map
    char *mapFile = "FRANCE.MAP";
    exitCode = mapReadDataFile(mapFile, map);
    if (exitCode != OK)
    {
        printError(exitCode);
        delVariables(map, route);
        return exitCode;
    }

    // Validate the city names
    City *startCity, *goalCity;
    if (!isValidNames(map, &startCity, (char *)startCityName, &goalCity, (char *)goalCityName))
    {
        printErrorUnknownName();
        printInstruction(map);
        delVariables(map, route);
        return 0;
    }

    // Perform the search
    exitCode = mapSearch(map, startCity, goalCity, route);
    if (exitCode != OK)
    {
        printError(exitCode);
        delVariables(map, route);
        return exitCode;
    }

    // Display the search result
    switch (route->nelts)
    {
    case 0:
        printf("Sorry, there is no route found from %s to %s in our database\n", startCity->name, goalCity->name);
        printInstruction(map);
        break;
    case 1:
        // User friendly message for the special case: start city == goal city
        printf("Special case: city 1 is identical to city 2. No further move needed.\n");
        break;
    default:
        printf("Result:\n");
        displayList(route);
    }

    // Clean the memory
    delVariables(map, route);

    return 0;
}
