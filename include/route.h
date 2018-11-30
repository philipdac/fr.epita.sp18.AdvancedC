#ifndef __route_H
#define __route_H

#include "city.h"
#include "List.h"
#include "status.h"

typedef struct Route
{
    struct City *city;
    struct City *prevCity;
    int distFromPrev;
    int costFromStart;
    int costToGoal;
} Route;

// Allocate memory for a route struct
//  @param city the city at the ending side
//  @param prevCity the city at the starting side
//  @param distance the distance between the 2 cities
//  @param costFromStart the cost from startCity to the prevCity
//  @return an pointer of empty route if memory allocation OK
//  @return 0 otherwise
Route *newFoundRoute(City *, City *, int, int);

// Allocate memory for a route struct
//  @param city the city at ending side of the route
//  @param prevCity the city at starting side of the route
//  @param distance the distance between the 2 cities
//  @param costFromStart the cost from startCity to the prevCity
//  @param goalCity the destination city for calculation the costToGoal
//  @return an pointer of empty route if memory allocation OK
//  @return 0 otherwise
Route *newRoute(City *, City *, int, int, City *);

// Compare route to to route by costToGoal
//  @param r1 the pointer to the route 1
//  @param r2 the pointer to the route 2
//  return int as the result of costToGoal1 - costToGoal2
int preferSmallCostToGoal(void *, void *);

// The later route is always < previous route, so that it pop out sooner
//  @param r1 the pointer to the route 1
//  @param r2 the pointer to the route 2
int LIFO(void *, void *);

// Free memory allocated to a route
void delRoute(void *);

// Check if the route existed in the provided list
//  @param list the list of routes
//  @param check the route that need to be checked
//  @param revertedCheck the route is checking in the reverted way, from city back to prevCity
//  @return pointer of the route found in list
//  @return 0 if not found
Route *isRouteInList(List *, Route *, int);

// Puts the route information into stdout
void printRoute(void *);

#endif
