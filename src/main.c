#include <stdio.h>
#include <string.h>

#include "city.h"
#include "common.h"
#include "List.h"
#include "route.h"
#include "map.h"

void getCityname(char *startCityName, char *goalCityName)
{
    printf("Searching for the shortest route between 2 cities.\n");

    printf(" - Enter the name of city 1: ");
    // Only get MAX_CITY_NAME_LENGTH from the keyboard
    fgets(startCityName, MAX_CITY_NAME_LENGTH, stdin);
    // fgets also get newline character into end of the string. Need to remove it
    startCityName[strcspn(startCityName, "\n")] = 0;

    printf(" - Enter the name of city 2: ");
    fgets(goalCityName, MAX_CITY_NAME_LENGTH, stdin);
    goalCityName[strcspn(goalCityName, "\n")] = 0;
}

int isValidSearchNames(List *map, City **startCity, char *startCityName, City **goalCity, char *goalCityName)
{
    *startCity = getCityByName(map, startCityName);
    *goalCity = getCityByName(map, goalCityName);

    if (!*startCity || !*goalCity)
    {
        printf("\nSearching for the route failed\n");
        printf("We can't find the entered name(s) in our database\n");
        printf("Please get city name from the below list: \n");
        displayList(map);

        return 0;
    }

    return -1;
}

int main(int argc, char const *argv[])
{
    status result;
    char startCityName[MAX_CITY_NAME_LENGTH];
    char goalCityName[MAX_CITY_NAME_LENGTH];

    City *startCity = 0, *goalCity = 0;

    // Initiate the map and routes
    List *map = newList(compareCityByName, printCityInfo);
    if (!map)
    {
        result = ERRALLOC;
        printf(message(result));
        return result;
    }

    List *route = newList(compareCityByName, printRoute);
    if (!route)
    {
        free(map);

        result = ERRALLOC;
        printf(message(result));
        return result;
    }

    // Read data to the map
    char *mapFile = "FRANCE.MAP";
    result = map_read_data_file(mapFile, map);
    if (result != OK)
    {
        printf(message(result));
        return result;
    }

    // Get city names
    if (argc == 3)
    {
        snprintf((char *)startCityName, MAX_CITY_NAME_LENGTH, (char *)argv[1]);
        snprintf((char *)goalCityName, MAX_CITY_NAME_LENGTH, (char *)argv[2]);
    }
    else
    {
        getCityname((char *)startCityName, (char *)goalCityName);
    }

    displayList(map);

    // Validate the city names
    if (!isValidSearchNames(map, &startCity, (char *)startCityName, &goalCity, (char *)goalCityName))
        return 0;

    printf("Seaching for route from %s to %s\n", startCity->name, goalCity->name);

    // Perform the search
    result = map_search(map, startCity, goalCity, route);
    if (result != OK)
    {
        printf(message(result));
        return result;
    }

    // Display the search result
    if (!lengthList(route))
    {
        printf("Sorry there is no route from %s to %s in our database", startCity->name, goalCity->name);
    }
    else
    {
        printf("Result:\n");
        displayList(route);
    }

    // Clean the memory
    delList(route);
    delList(map);

    return 0;
}
