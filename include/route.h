#ifndef __route_H
#define __route_H

#include "city.h"
#include "List.h"
#include "status.h"

typedef struct Route
{
    struct City *city;
    struct Route *prevRoute;
    int distFromPrev;
    int costFromStart;
    int costToGoal;
} Route;

// Allocate memory for a route struct
//  @param city the city that the route reaches
//  @param prevRoute the previous route
//  @param distance the distance from previous city to this city
//  @param cost the cost from start city to this city
//  @return an pointer of empty route if memory allocation OK
//  @return 0 otherwise
Route *newFoundRoute(City *, Route *, int, int);

// Allocate memory for a route struct
//  @param city the city that the route reaches
//  @param prevRoute the previous route
//  @param distance the distance from previous city to this city
//  @param cost the cost from start city to this city
//  @param goalCity the destination city for calculation the costToGoal
//  @return an pointer of empty route if memory allocation OK
//  @return 0 otherwise
Route *newRoute(City *, Route *, int, int, City *);

// Compare route to route by total cost (actual cost from start + estimated cost to goal)
//  @param r1 the pointer to the route 1
//  @param r2 the pointer to the route 2
//  return int as the result of costToGoal1 - costToGoal2
int compareTotalCost(void *, void *);

// The later route is always < previous route, so that it pop out earlier
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
