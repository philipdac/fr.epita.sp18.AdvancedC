#include "common.h"
#include "List.h"

typedef struct Neighbor
{
    char name[MAX_CITY_NAME_LENGTH];
    int distance;
} Neighbor;

typedef struct City
{
    char name[MAX_CITY_NAME_LENGTH];
    int posX;
    int posY;
    struct List *neighbors;
} City;

// Allocate memory for a city struct
//  return an pointer of empty city if memory allocation OK
//  return 0 otherwise
City *newCity();

// Compare city to city by name
//  @param city1 the pointer to the city1
//  @param city2 the pointer to the city2
//  return int as the result of strcmpi
int compareCity(void *, void *);

// free memory allocated to a city
void delCity(City *city);

// puts the city->name to stdout
void printCityname(void *);

// set the cityname
//  @param city the city that has the name
//  @param name the name to be set
void setCityname(City *, char *);
