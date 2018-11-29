#ifndef __route_H
#define __route_H

#include "city.h"
#include "List.h"
#include "status.h"

int goalLatitude;
int goalLongitude;

typedef struct Route
{
    struct City *city;
    struct City *prevCity;
    int distFromPrev;
    int costFromStart;
    int costToGoal;
} Route;

// Allocate memory for a route struct
//  return an pointer of empty route if memory allocation OK
//  return 0 otherwise
Route *newRoute();

// Compare route to to route by costToGoal
//  @param r1 the pointer to the route 1
//  @param r2 the pointer to the route 2
//  return int as the result of costToGoal1 - costToGoal2
int compareRoute(void *, void *);

// free memory allocated to a route
void delRoute(Route *);

// puts the route information into stdout
void printRoute(void *);

#endif
