#include <stdio.h>
#include <string.h>

#include "city.h"
#include "common.h"
#include "List.h"
#include "map.h"
#include "route.h"
#include "string_ext.h"

void printError(status code)
{
    printf("Run time error: %s\n", message(code));
}

void printErrorIdenticalName()
{
    printf("You have input the same name for 2 cities.\n");
    printf("Let's use 2 different names instead.\n");
}

void printErrorUnknownName()
{
    printf("We can't find the entered name(s) in our database\n");
    printf("Route searching failed\n");
}

void printInstruction(List *map)
{
    printf("Please use city name in the below list: \n");
    displayList(map);
}

void getCityname(int argc, char const *argv[], char *startCityName, char *goalCityName)
{
    if (argc == 3)
    {
        snprintf((char *)startCityName, MAX_CITY_NAME_LENGTH, argv[1]);
        snprintf((char *)goalCityName, MAX_CITY_NAME_LENGTH, argv[2]);
        return;
    }

    printf("Searching for the shortest routeList between 2 cities.\n");

    printf(" - Enter the name of city 1: ");
    // Only get MAX_CITY_NAME_LENGTH from the keyboard
    fgets(startCityName, MAX_CITY_NAME_LENGTH, stdin);
    // fgets also get newline character into end of the string. Need to remove it
    startCityName[strcspn(startCityName, "\n")] = 0;

    printf(" - Enter the name of city 2: ");
    fgets(goalCityName, MAX_CITY_NAME_LENGTH, stdin);
    goalCityName[strcspn(goalCityName, "\n")] = 0;
}

int isIdenticalName(char *name1, char *name2)
{
    return strcpm_insensitive(name1, name2) == 0;
}

int isValidNames(List *map, City **startCity, char *startCityName, City **goalCity, char *goalCityName)
{
    *startCity = getCityByName(map, startCityName);
    *goalCity = getCityByName(map, goalCityName);

    if (!*startCity || !*goalCity)
    {
        printInstruction(map);
        return 0;
    }

    return -1;
}

status initVariables(List **map, List **routeList)
{
    *map = newList(compareCityByName, printCityInfo);
    if (!(*map))
    {
        return ERRALLOC;
    }

    *routeList = newList(LIFO, printRoute);
    if (!(*routeList))
    {
        free(map);
        return ERRALLOC;
    }

    return OK;
}

void delVariables(List *map, List *routeList)
{
    forEach(routeList, delRoute);
    delList(routeList);

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

    // Reject when both names are identical
    if (isIdenticalName(startCityName, goalCityName))
    {
        printErrorIdenticalName();
        return 0;
    }

    // Initiate the map and routes
    List *map, *routeList;
    exitCode = initVariables(&map, &routeList);
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
        delVariables(map, routeList);
        return exitCode;
    }

    // Validate the city names
    City *startCity, *goalCity;
    if (!isValidNames(map, &startCity, (char *)startCityName, &goalCity, (char *)goalCityName))
    {
        printErrorUnknownName();
        printInstruction(map);
        delVariables(map, routeList);
        return 0;
    }

    // Perform the search
    exitCode = mapSearch(map, startCity, goalCity, routeList);
    if (exitCode != OK)
    {
        printError(exitCode);
        delVariables(map, routeList);
        return exitCode;
    }

    // Display the search exitCode
    if (!lengthList(routeList))
    {
        printf("Sorry there is no route from %s to %s in our database", startCity->name, goalCity->name);
    }
    else
    {
        printf("Result:\n");
        displayList(routeList);
    }

    // Clean the memory
    delVariables(map, routeList);

    return 0;
}
