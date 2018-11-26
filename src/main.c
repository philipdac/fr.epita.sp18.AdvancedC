#include <stdio.h>
#include <string.h>

#include "city.h"
#include "common.h"
#include "List.h"
#include "map.h"

void getCityname(City *fromCity, City *toCity)
{
    printf("Searching for the shortest route between 2 cities.\n");

    printf("Enter name of city 1: ");
    fgets(fromCity->name, MAX_CITY_NAME_LENGTH, stdin);
    // fgets also get newline character into end of the string. Need to remove it
    fromCity->name[strcspn(fromCity->name, "\n")] = 0;

    printf("Enter name of city 2: ");
    fgets(toCity->name, MAX_CITY_NAME_LENGTH, stdin);
    toCity->name[strcspn(toCity->name, "\n")] = 0;
}

int main(int argc, char const *argv[])
{
    status result;

    City *fromCity = newCity();
    City *toCity = newCity();
    if (!fromCity && !toCity)
        return ERRALLOC;

    if (argc != 3)
    {
        getCityname(fromCity, toCity);
    }
    else
    {
        setCityname(fromCity, (char *)argv[1]);
        setCityname(toCity, (char *)argv[2]);
    }

    List *map = newList(compareCity, printCityInfo);
    if (!map)
        return ERRALLOC;

    char *mapFile = "FRANCE.MAP";
    if (result = map_file_to_list(mapFile, map))
        return result;

    // test
    printf("Compare = %d\n", compareCity(fromCity, toCity));

    displayList(map);
    // end test

    delList(map);

    return 0;
}
