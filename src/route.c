#include <limits.h>
#include <stdio.h>

#include "route.h"

// Allocate memory for a route node struct
//  return an pointer of empty route node if memory allocation OK
//  return 0 otherwise
RouteNode *newRouteNode()
{
    RouteNode *node = malloc(sizeof(RouteNode));
    if (!node)
        return 0;

    node->prevCity = 0;
    node->distFromPrev = INT_MAX;
    node->distFromStart = INT_MAX;
    node->distToGoal = INT_MAX;

    return node;
}

// free memory allocated to a route node
void delRouteNode(RouteNode *node)
{
    if (!node)
        free(node);
}

// puts the route node information into stdout
void printRouteNode(void *city)
{
    printf("(%s -> %s : %dkm)", ((City *)city)->routeNode->prevCity->name, ((City *)city)->name, ((City *)city)->routeNode->distFromPrev);
}
