#include <stdio.h>
#include <string.h>

#include "city.h"
#include "common.h"
#include "List.h"
#include "map.h"

void getCityname(char *fromName, char *toName)
{
    printf("Searching for the shortest route between 2 cities.\n");

    printf(" - Enter the name of city 1: ");
    // Only get MAX_CITY_NAME_LENGTH from the keyboard
    fgets(fromName, MAX_CITY_NAME_LENGTH, stdin);
    // fgets also get newline character into end of the string. Need to remove it
    fromName[strcspn(fromName, "\n")] = 0;

    printf(" - Enter the name of city 2: ");
    fgets(toName, MAX_CITY_NAME_LENGTH, stdin);
    toName[strcspn(toName, "\n")] = 0;
}

int isValidSearchNames(List *map, City **fromCity, char *fromName, City **toCity, char *toName)
{
    *fromCity = isValidCity(map, fromName);
    *toCity = isValidCity(map, toName);

    if (!*fromCity || !*toCity)
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
    char fromName[MAX_CITY_NAME_LENGTH];
    char toName[MAX_CITY_NAME_LENGTH];

    City *fromCity = 0, *toCity = 0;

    // Initiate the map and routes
    List *map = newList(compareCity, printCityInfo);
    if (!map)
    {
        result = ERRALLOC;
        printf(message(result));
        return result;
    }

    List *route = newList(compareCity, printCityInfo);
    if (!route)
    {
        free(map);

        result = ERRALLOC;
        printf(message(result));
        return result;
    }

    // Read data to the map
    char *mapFile = "FRANCE.MAP";
    result = map_file_to_list(mapFile, map);
    if (result != OK)
    {
        printf(message(result));
        return result;
    }

    // Get city names
    if (argc == 3)
    {
        snprintf((char *)fromName, MAX_CITY_NAME_LENGTH, (char *)argv[1]);
        snprintf((char *)toName, MAX_CITY_NAME_LENGTH, (char *)argv[2]);
    }
    else
    {
        getCityname((char *)fromName, (char *)toName);
    }

    // Validate the city names
    if (!isValidSearchNames(map, &fromCity, (char *)fromName, &toCity, (char *)toName))
        return 0;

    search_route(map, fromCity, toCity, route);

    // test
    // displayList(map);
    // end test

    // Clean the memory
    delList(map);
    delList(route);

    return 0;
}
