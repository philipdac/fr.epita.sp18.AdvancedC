#include <stdio.h>
#include <string.h>

#include "city.h"
#include "List.h"
#include "string_ext.h"
#include "vertex.h"

// return an empty city pointer if memory allocation OK
// return 0 otherwise
City *newCity()
{
    List *neighborList = newList(compareNeighborByDistance, printNeighborInfo);
    if (!neighborList)
    {
        return 0;
    }

    City *city = malloc(sizeof(City));
    if (!city)
    {
        delList(neighborList);
        return 0;
    }

    neighborList->head = 0;
    neighborList->nelts = 0;

    city->name[0] = 0;
    city->neighbors = neighborList;
    city->latitude = 0;
    city->longitude = 0;

    return city;
}

// Allocate memory for a neighbor struct and set the its information
//  @param city the city that is playing a role of neighbor
//  @param distance the distance between this city and the previous one
//  return an pointer of neighbor if memory allocation OK
//  return 0 otherwise
Neighbor *newNeighbor(City *city, int distance)
{
    Neighbor *neighbor = malloc(sizeof(Neighbor));
    if (!neighbor)
        return 0;

    neighbor->city = city;
    neighbor->distance = distance;

    return neighbor;
}

// Compare city to city by name
//  @param city1 the pointer to the city1
//  @param city2 the pointer to the city2
//  return int as the result of strcpm_insensitive
int compareCityByName(void *city1, void *city2)
{
    return strcpm_insensitive(((City *)city1)->name, ((City *)city2)->name);
}

// Compare neighbor to neighbor by their distance to the city
//  @param n1 the pointer to the neighbor 1
//  @param n2 the pointer to the neighbor 2
//  return int
int compareNeighborByDistance(void *n1, void *n2)
{
    return ((Neighbor *)n1)->distance - ((Neighbor *)n2)->distance;
}

// Free memory allocated to a city
//  @param city the city need to be deleted
void delCity(void *city)
{
    if (!city)
        return;

    if (((City *)city)->neighbors)
    {
        // free memory allocated to the neighbor list
        forEach(((City *)city)->neighbors, delNeighbor);
        delList(((City *)city)->neighbors);
    }

    free(city);
}

// Free memory allocated to a neighbor
void delNeighbor(void *neighbor)
{
    if (!neighbor)
        return;

    free(neighbor);
}

// Get the cityname in the list by its name
//  @param map the list of city
//  @param name the cityname
//  return pointer to the City if found; 0 if not found
City *getCityByName(List *map, char *name)
{
    City *city = newCity();

    if (!city)
    {
        printf(message(ERRALLOC));
        return 0;
    }

    setCityname(city, name);
    Node *node = isInList(map, city);
    free(city);

    if (node == (Node *)0)
        return 0;
    else if (node == (Node *)1)
        return (City *)map->head->val;

    return (City *)node->next->val;
}

// puts the city->name to stdout
//  @param city the city that has the name to be printed
void printCityInfo(void *city)
{
    printf("%s", ((City *)city)->name);

    // Display neighbor name for testing purpose only
    // printf("\n");
    // printf("%s, position : %d/%d, neighbors : %d\n", ((City *)city)->name, ((City *)city)->latitude, ((City *)city)->longitude, ((City *)city)->neighbors->nelts);
    // displayList(((City *)city)->neighbors);
}

// puts the neighbor information into stdout
void printNeighborInfo(void *n)
{
    printf("(%s, %d)", ((Neighbor *)n)->city->name, ((Neighbor *)n)->distance);
}

// set the cityname
//  @param city the city that has the name
//  @param name the name to be set
//  @param latitude the latitude to be set
//  @param longitude the longitude to be set
void setCityInfo(City *city, char *name, int latitude, int longitude)
{
    if (!city)
        return;

    setCityname(city, name);
    city->latitude = latitude;
    city->longitude = longitude;
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
