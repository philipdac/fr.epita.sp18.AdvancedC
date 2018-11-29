#include <limits.h>
#include <stdio.h>

#include "common.h"
#include "city.h"
#include "List.h"
#include "route.h"
#include "status.h"

status updateFoundRoute(List *closedList, List *routeList)
{
    status stat;
    int i, len = closedList->nelts;
    Route *route;
    for (i = 1; i <= len; i++)
    {
        stat = nthInList(closedList, i, (void *)&route);
        if (stat != OK)
            return stat;
        stat = addList(routeList, route);
        if (stat != OK)
            return stat;
    }
}

// Search the shortest route between startCity and goalCity
//  @param map the map where we perform our search
//  @param startCity the starting city
//  @param goalCity the destination city
//  @param route the result route
//  @ return ERRINDEX if any error occurs during the search
//  @ return OK otherwise
status map_search(List *map, City *startCity, City *goalCity, List *route)
{
    if (!map || !route)
        return ERREMPTY;

    status stat;

    List *openList = newList(compareRoute, printRoute);
    List *closedList = newList(compareRoute, printRoute);

    Route *start = newRoute(startCity, 0, 0, 0, goalCity);
    if (!start)
        return ERRALLOC;

    stat = addList(openList, start);
    if (stat != OK)
        return stat;

    int found = 0;
    while (openList->nelts > 0 && !found)
    {
        Route *current;
        // The top node in openList has lowest costToGoal
        stat = nthInList(openList, 1, (void *)&current);

        int i;
        for (i = 1; i <= current->city->neighbors->nelts; i++)
        {
            Neighbor *nei;
            stat = nthInList(current->city->neighbors, i, (void *)&nei);
            if (stat != OK)
                return stat;

            Route *nextRoute = newRoute(nei->city, current->city, nei->distance, current->costFromStart, goalCity);

            if (nei->city != goalCity)
            {
                // nextCity existed in openList?
                Route *existed = isRouteInList(openList, nextRoute);
                if (!existed)
                {
                    addList(openList, nextRoute);
                }
                else if (existed->costToGoal > nextRoute->costToGoal)
                {
                    // This route is faster and need to be consider
                    // otherwise, just ignore it
                    addList(openList, nextRoute);
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

        addList(closedList, current);
    }

    stat = updateFoundRoute(closedList, route);
    if (stat != OK)
        return stat;

    return OK;
}
