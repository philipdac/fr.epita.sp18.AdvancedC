#ifndef __route_H
#define __route_H

#include "city.h"
#include "List.h"
#include "status.h"

typedef struct RouteNode
{
    struct City *prevCity;
    int distFromPrev;

    // distFromStart is 0 for the route node of the starting city
    // distFromStart is INT_MAX for unvisited city
    int distFromStart;

    // distToGoal is 0 for the route node of the destination city
    int distToGoal;
} RouteNode;

// Allocate memory for a route node struct
//  return an pointer of empty route node if memory allocation OK
//  return 0 otherwise
RouteNode *newRouteNode();

// free memory allocated to a route node
void delRouteNode(RouteNode *);

// puts the route node information into stdout
void printRouteNode(void *);

#endif
