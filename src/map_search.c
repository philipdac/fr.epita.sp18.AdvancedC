#include <limits.h>
#include <stdio.h>

#include "common.h"
#include "city.h"
#include "List.h"
#include "status.h"

// Search the shortest route between fromCity and toCity
//  @param map the map where we perform our search
//  @param fromCity the starting city
//  @param toCity the destination city
//  @param route the result route
//  @ return ERRINDEX if any error occurs during the search
//  @ return OK otherwise
status map_search(List *map, City *fromCity, City *toCity, List *route)
{
    if (!map || !route)
        return ERREMPTY;

    List *unvisited = map;
    List *visited = newList(compareCity, printRouteNode);

    if (!visited)
        return ERRALLOC;

    fromCity->routeNode->distFromStart = 0;
    toCity->routeNode->distToGoal = 0;

    // Special case
    if (compareCity(fromCity, toCity) == 0)
    {
        toCity->routeNode->prevCity = fromCity;
        toCity->routeNode->distFromStart = 0;
        toCity->routeNode->distFromPrev = 0;
        addList(route, fromCity);
    }

    return OK;
}
