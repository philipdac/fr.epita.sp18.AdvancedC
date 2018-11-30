#include <limits.h>
#include <stdio.h>

#include "common.h"
#include "city.h"
#include "List.h"
#include "route.h"
#include "status.h"

status linkFoundRoutes(List *closedList, List *routeList, Route *finalRoute)
{
    status stat;
    int i, len = closedList->nelts;
    City *city = finalRoute->city;
    Route *route;

    for (i = 1; i <= len; i++)
    {
        stat = nthInList(closedList, i, (void *)&route);
        if (stat != OK)
            return stat;

        // Many routes in the closedList
        // Take only the required chain
        if (city == route->city && route->prevCity)
        {
            Route *found = newFoundRoute(route->city, route->prevCity, route->distFromPrev, route->costFromStart);
            stat = addList(routeList, found);
            if (stat != OK)
                return stat;

            city = route->prevCity;
        }
    }

    return OK;
}

int isGoodRoute(List *openList, List *closedList, Route *route)
{
    Route *inList;

    // route existed in openList?
    inList = isRouteInList(openList, route, 0);
    if (inList && inList->costToGoal > route->costToGoal)
    {
        // This route is faster and need to be consider
        // otherwise, just ignore it
        return -1;
    }
    else
    {
        // route existed in closedList?
        inList = isRouteInList(closedList, route, 0);
        if (inList && inList->costToGoal > route->costToGoal)
        {
            // This route is faster and need to be reconsider
            // otherwise, just ignore it
            return -1;
        }
        else
        {
            // It is a new route.
            // No point to go to a city then go back --> Ignore this route if reverted route existed
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

    status stat;

    List *openList = newList(preferSmallCostToGoal, printRoute);
    List *closedList = newList(LIFO, printRoute);
    if (!openList || !closedList)
        return ERRALLOC;

    Route *current, *nextRoute;
    Route *start = newRoute(startCity, 0, 0, 0, goalCity);
    if (!start)
    {
        freeMemMapSearch(openList, closedList);
        return ERRALLOC;
    }

    stat = addList(openList, start);
    if (stat != OK)
    {
        freeMemMapSearch(openList, closedList);
        return stat;
    }

    int found = 0;
    while (openList->nelts > 0 && !found)
    {
        // The top node in openList has lowest costToGoal
        stat = nthInList(openList, 1, (void *)&current);

        stat = addList(closedList, current);
        if (stat != OK)
        {
            freeMemMapSearch(openList, closedList);
            return stat;
        }

        stat = remFromList(openList, current);
        if (stat != OK)
        {
            freeMemMapSearch(openList, closedList);
            return stat;
        }

        int i;
        for (i = 1; i <= current->city->neighbors->nelts; i++)
        {
            Neighbor *nei;
            stat = nthInList(current->city->neighbors, i, (void *)&nei);
            if (stat != OK)
            {
                freeMemMapSearch(openList, closedList);
                return stat;
            }

            nextRoute = newRoute(nei->city, current->city, nei->distance, nei->distance + current->costFromStart, goalCity);

            if (nei->city != goalCity)
            {
                if (isGoodRoute(openList, closedList, nextRoute))
                    addList(openList, nextRoute);
            }
            else
            {
                // Reach the destination
                addList(closedList, nextRoute);
                found = -1;
                break;
            }
        }
    }

    stat = linkFoundRoutes(closedList, routeList, nextRoute);
    if (stat != OK)
    {
        freeMemMapSearch(openList, closedList);
        return stat;
    }

    freeMemMapSearch(openList, closedList);
    return OK;
}
