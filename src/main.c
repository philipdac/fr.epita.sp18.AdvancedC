#include <stdio.h>
#include <string.h>

#include "city.h"
#include "common.h"
#include "List.h"
#include "map.h"

int main(int argc, char const *argv[])
{
    City *fromCity = newCity();
    City *toCity = newCity();

    if (argc != 3)
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
    else
    {
        setCityname(fromCity, (char *)argv[1]);
        setCityname(toCity, (char *)argv[2]);
    }

    char *filename = "FRANCE.MAP";
    List *maps = newList(compareCity, printCityname);

    read_file_map(filename, maps);

    // test
    printf("Compare %d", compareCity(fromCity, toCity));

    addList(maps, fromCity);
    addList(maps, toCity);

    displayList(maps);
    // end test

    return 0;
}
