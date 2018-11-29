#include <limits.h>
#include <stdio.h>

#include "common.h"
#include "city.h"
#include "List.h"
#include "route.h"
#include "status.h"

status updateFoundRoute(List *closedList, List *routeList, Route *finalRoute)
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
            stat = addList(routeList, route);
            if (stat != OK)
                return stat;

            city = route->prevCity;
        }
    }

    return OK;
}

// Search the shortest route between startCity and goalCity
//  @param map the map where we perform our search
//  @param startCity the starting city
//  @param goalCity the destination city
//  @param route the result route
//  @ return ERRINDEX if any error occurs during the search
//  @ return OK otherwise
status map_search(List *map, City *startCity, City *goalCity, List *routeList)
{
    if (!map || !routeList)
        return ERREMPTY;

    status stat;

    List *openList = newList(preferSmallCostToGoal, printRoute);
    List *closedList = newList(LIFO, printRoute);

    Route *current, *nextRoute;
    Route *start = newRoute(startCity, 0, 0, 0, goalCity);
    if (!start)
        return ERRALLOC;

    stat = addList(openList, start);
    if (stat != OK)
        return stat;

    int found = 0;
    while (openList->nelts > 0 && !found)
    {
        // The top node in openList has lowest costToGoal
        stat = nthInList(openList, 1, (void *)&current);

        stat = addList(closedList, current);
        if (stat != OK)
            return stat;

        stat = remFromList(openList, current);
        if (stat != OK)
            return stat;

        int i;
        for (i = 1; i <= current->city->neighbors->nelts; i++)
        {
            Neighbor *nei;
            stat = nthInList(current->city->neighbors, i, (void *)&nei);
            if (stat != OK)
                return stat;

            nextRoute = newRoute(nei->city, current->city, nei->distance, nei->distance + current->costFromStart, goalCity);

            if (nei->city != goalCity)
            {
                // nextCity existed in openList?
                Route *inOpenList = isRouteInList(openList, nextRoute, 0);
                if (inOpenList && inOpenList->costToGoal > nextRoute->costToGoal)
                {
                    // This route is faster and need to be consider
                    // otherwise, just ignore it
                    addList(openList, nextRoute);
                }
                else
                {
                    // nextCity existed in closedList?
                    Route *inClosedList = isRouteInList(closedList, nextRoute, 0);
                    if (inClosedList && inClosedList->costToGoal > nextRoute->costToGoal)
                    {
                        // This route is faster and need to be consider
                        // otherwise, just ignore it
                        addList(openList, nextRoute);
                    }
                    else
                    {
                        // Not in both list
                        // Check if reverted route existed
                        Route *reverted = isRouteInList(closedList, nextRoute, -1);
                        if (!reverted)
                            addList(openList, nextRoute);
                    }
                }
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

    stat = updateFoundRoute(closedList, routeList, nextRoute);
    if (stat != OK)
        return stat;

    return OK;
}
