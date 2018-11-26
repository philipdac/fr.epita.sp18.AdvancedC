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

// Allocate memory for a neighbor struct and set the its information
//  @param city the city that connects with the neighbor
//  @param neighbor theneighbor that has the name
//  @param name the name to be set
//  @param distance the distance between city and the neighbor
//  return an pointer of empty neighbor if memory allocation OK
//  return 0 otherwise
Neighbor *newNeighbor(City *, char *, int);

// Compare city to city by name
//  @param city1 the pointer to the city1
//  @param city2 the pointer to the city2
//  return int as the result of strcmpi
int compareCity(void *, void *);

// free memory allocated to a city
void delCity(City *);

// free memory allocated to a neighbor
void delNeighbor(Neighbor *);

// Check if the city is in the map
//  @param map the list of city
//  @param city the city that need to validate
//  return int as the result of isInList
int isValidCity(List *, City *);

// puts the city information into stdout
void printCityInfo(void *);

// puts the neighbor information into stdout
void printNeighborInfo(void *);

// set the city information
//  @param city the city that has the name
//  @param name the name to be set
//  @param posX the posX to be set
//  @param posY the posY to be set
void setCityInfo(City *, char *, int, int);

// set the cityname
//  @param city the city that has the name
//  @param name the name to be set
void setCityname(City *, char *);
