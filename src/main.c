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
    City *fromCity = newCity();
    City *toCity = newCity();

    if (argc != 3)
    {
        getCityname(fromCity, toCity);
    }
    else
    {
        setCityname(fromCity, (char *)argv[1]);
        setCityname(toCity, (char *)argv[2]);
    }

    List *mapList = newList(compareCity, printCityname);
    char *mapFile = "FRANCE.MAP";
    map_file_to_list(mapFile, mapList);

    // test
    printf("Compare = %d\n", compareCity(fromCity, toCity));

    addList(mapList, fromCity);
    addList(mapList, toCity);

    displayList(mapList);
    // end test

    return 0;
}
