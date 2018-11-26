#include <stdio.h>
#include <string.h>

#include "city.h"

// return an empty city pointer if memory allocation OK
// return 0 otherwise
City *newCity()
{
    City *city = malloc(sizeof(City));
    if (!city)
        return 0;

    city->name[0] = 0;
    city->neighbors = 0;
    city->posX = 0;
    city->posY = 0;

    return city;
}

// Compare city to city by name
//  @param city1 the pointer to the city1
//  @param city2 the pointer to the city2
//  return int as the result of strcmpi
int compareCity(void *city1, void *city2)
{
    return strcmpi(((City *)city1)->name, ((City *)city2)->name);
}

// free memory allocated to a city
//  @param city the city need to be deleted
void delCity(City *city)
{
    if (!city)
        return;

    if (city->neighbors)
    {
        // free memory allocated to the neighbor list
    }

    free(city);
}

// puts the city->name to stdout
//  @param city the city that has the name to be printed
void printCityname(void *city)
{
    printf(((City *)city)->name);
}

// set the cityname
//  @param city the city that has the name
//  @param name the name to be set
void setCityname(City *city, char *name)
{
    if (!city)
        return;

    snprintf(city->name, MAX_CITY_NAME_LENGTH, name);
}
