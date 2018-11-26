#ifndef __city_H
#define __city_H

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
    int latitude;
    int longitude;
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

// Compare neighbor to neighbor by their distance to the city
//  @param n1 the pointer to the neighbor 1
//  @param n2 the pointer to the neighbor 2
//  return int
int compareNeighbor(void *, void *);

// free memory allocated to a city
void delCity(City *);

// free memory allocated to a neighbor
void delNeighbor(Neighbor *);

// Check if the cityname is in the map
//  @param map the list of city
//  @param name the cityname that need to validate
//  return pointer to the City if found; 0 if not found
City *isValidCity(List *, char *);

// puts the city information into stdout
void printCityInfo(void *);

// puts the neighbor information into stdout
void printNeighborInfo(void *);

// set the city information
//  @param city the city that has the name
//  @param name the name to be set
//  @param latitude the latitude to be
//  @param longitude the longitude to be set
void setCityInfo(City *, char *, int, int);

// set the cityname
//  @param city the city that has the name
//  @param name the name to be set
void setCityname(City *, char *);

#endif
