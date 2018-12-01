#include <limits.h>
#include <stdio.h>

#include "common.h"
#include "city.h"
#include "List.h"
#include "route.h"
#include "status.h"

status linkFoundRoutes(List *routeList, Route *finalRoute)
{
    status exitCode;
    Route *route = finalRoute;

    while (route->prevRoute)
    {
        Route *found = newFoundRoute(route->city, route->prevRoute, route->distFromPrev, route->costFromStart);
        exitCode = addList(routeList, found);
        if (exitCode != OK)
            return exitCode;

        route = route->prevRoute;
    }

    return OK;
}

int isGoodRoute(List *openList, List *closedList, Route *route)
{
    Route *inList;

    // route existed in openList?
    inList = isRouteInList(openList, route, 0);
    if (inList && (inList->costFromStart + inList->costToGoal) > (route->costFromStart + route->costToGoal))
    {
        // This route is faster and need to be considered (good route)
        return -1;
    }
    else
    {
        // route existed in closedList?
        inList = isRouteInList(closedList, route, 0);
        if (inList && (inList->costFromStart + inList->costToGoal) > (route->costFromStart + route->costToGoal))
        {
            // This route is faster and need to be reconsidered (good route)
            return -1;
        }
        else
        {
            // It is a new route, then we need to check if we have used this route in a reverted way
            // as it does not make sense to go to a city then go back --> Ignore this route if reverted route existed
            inList = isRouteInList(closedList, route, -1);
            if (!inList)
            {
                inList = isRouteInList(openList, route, -1);
                if (!inList)
                    // A completely new route
                    return -1;
            }
        }
    }

    return 0;
}

void freeMemMapSearch(List *openList, List *closedList)
{
    forEach(openList, delRoute);
    delList(openList);

    forEach(closedList, delRoute);
    delList(closedList);
}

// Search the shortest route between startCity and goalCity
//  @param map the map where we perform our search
//  @param startCity the starting city
//  @param goalCity the destination city
//  @param route the result route
//  @ return ERRINDEX if any error occurs during the search
//  @ return OK otherwise
status mapSearch(List *map, City *startCity, City *goalCity, List *routeList)
{
    if (!map || !routeList)
        return ERREMPTY;

    status exitCode;

    List *openList = newList(compareTotalCost, printRoute);

    // LIFO is the nature of a stack. Function LIFO does not compare anything.
    // Just use this function for better running speed vs. other comparision function
    List *closedList = newList(LIFO, printRoute);
    if (!openList || !closedList)
        return ERRALLOC;

    Route *currentRoute, *nextRoute;
    Route *firstRoute = newRoute(startCity, 0, 0, 0, goalCity);
    if (!firstRoute)
    {
        freeMemMapSearch(openList, closedList);
        return ERRALLOC;
    }

    exitCode = addList(openList, firstRoute);
    if (exitCode != OK)
    {
        freeMemMapSearch(openList, closedList);
        return exitCode;
    }

    int found = 0;
    while (openList->nelts > 0 && !found)
    {
        // The top node in openList has lowest costToGoal
        exitCode = nthInList(openList, 1, (void *)&currentRoute);

        exitCode = addList(closedList, currentRoute);
        if (exitCode != OK)
        {
            freeMemMapSearch(openList, closedList);
            return exitCode;
        }

        exitCode = remFromList(openList, currentRoute);
        if (exitCode != OK)
        {
            freeMemMapSearch(openList, closedList);
            return exitCode;
        }

        int i;
        for (i = 1; i <= currentRoute->city->neighbors->nelts; i++)
        {
            Neighbor *nei;
            exitCode = nthInList(currentRoute->city->neighbors, i, (void *)&nei);
            if (exitCode != OK)
            {
                freeMemMapSearch(openList, closedList);
                return exitCode;
            }

            nextRoute = newRoute(nei->city, currentRoute, nei->distance, nei->distance + currentRoute->costFromStart, goalCity);

            if (nei->city == goalCity)
            {
                // Reach the destination
                // This may not the shortest route but the A* algo try to get the result as fast as possible
                addList(closedList, nextRoute);
                found = -1;
                break;
            }
            else if (isGoodRoute(openList, closedList, nextRoute))
            {
                addList(openList, nextRoute);
            }
        }
    }

    exitCode = linkFoundRoutes(routeList, nextRoute);
    freeMemMapSearch(openList, closedList);

    return exitCode;
}
