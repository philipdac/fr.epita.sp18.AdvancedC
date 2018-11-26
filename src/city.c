#include <stdio.h>
#include <string.h>

#include "city.h"
#include "List.h"

// return an empty city pointer if memory allocation OK
// return 0 otherwise
City *newCity()
{
    List *neighborList = newList(compareCity, printNeighborInfo);
    City *city = malloc(sizeof(City));
    if (!city || !neighborList)
        return 0;

    neighborList->head = 0;
    neighborList->nelts = 0;

    city->name[0] = 0;
    city->neighbors = neighborList;
    city->posX = 0;
    city->posY = 0;

    return city;
}

// Allocate memory for a neighbor struct and set the its information
//  @param city the city that connects with the neighbor
//  @param neighbor theneighbor that has the name
//  @param name the name to be set
//  @param distance the distance between city and the neighbor
//  return an pointer of empty neighbor if memory allocation OK
//  return 0 otherwise
Neighbor *newNeighbor(City *city, char *name, int distance)
{
    Neighbor *neighbor = malloc(sizeof(Neighbor));
    if (!neighbor)
        return 0;

    snprintf(neighbor->name, MAX_CITY_NAME_LENGTH, name);
    neighbor->distance = distance;

    status s = addList(city->neighbors, neighbor);
    if (s != OK)
    {
        // addList has error, free the allocated memory and return 0;
        free(neighbor);
        return 0;
    }

    return neighbor;
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
        delList(city->neighbors);
    }

    free(city);
}

// puts the city->name to stdout
//  @param city the city that has the name to be printed
void printCityInfo(void *city)
{
    printf("\n");
    printf("%s, position : %d/%d, neighbors : %d\n", ((City *)city)->name, ((City *)city)->posX, ((City *)city)->posY, ((City *)city)->neighbors->nelts);
    displayList(((City *)city)->neighbors);
}

// puts the neighbor information into stdout
void printNeighborInfo(void *n)
{
    printf("(%s, %d)", ((Neighbor *)n)->name, ((Neighbor *)n)->distance);
}

// set the cityname
//  @param city the city that has the name
//  @param name the name to be set
//  @param posX the posX to be set
//  @param posY the posY to be set
void setCityInfo(City *city, char *name, int posX, int posY)
{
    if (!city)
        return;

    setCityname(city, name);
    city->posX = posX;
    city->posY = posY;
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
