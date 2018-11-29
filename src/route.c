#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "route.h"

int getCostToGoal(City *city, City *goalCity)
{
    int gap1 = city->latitude - goalCity->latitude;
    int gap2 = city->longitude - goalCity->longitude;

    return gap1 * gap1 + gap2 * gap2;
}

// Allocate memory for a route struct
//  @param city the city at the ending side
//  @param prevCity the city at the starting side
//  @param distance the distance between the 2 cities
//  @param costFromStart the cost from startCity to the prevCity
//  @param goalCity the destination city for calculation the costToGoal
//  @return an pointer of empty route if memory allocation OK
//  @return 0 otherwise
Route *newRoute(City *city, City *prevCity, int distance, int costFromStart, City *goalCity)
{
    Route *route = malloc(sizeof(Route));
    if (!route)
        return 0;

    route->city = city;
    route->prevCity = prevCity;
    route->distFromPrev = distance;
    route->costFromStart = costFromStart;
    route->costToGoal = getCostToGoal(city, goalCity);

    return route;
}

// Compare route to route by costToGoal to have the better one
//  @param r1 the pointer to the route 1
//  @param r2 the pointer to the route 2
//  @return int as the differences between the two costToGoal
int compareRoute(void *r1, void *r2)
{
    return ((Route *)r1)->costToGoal - ((Route *)r1)->costToGoal;
}

// Free memory allocated to a route
void delRoute(Route *route)
{
    if (!route)
        free(route);
}

// Check if the route existed in the provided list
//  @param list the list of routes
//  @param check the route that need to be checked
//  @return pointer of the route found in list
//  @return 0 if not found
Route *isRouteInList(List *list, Route *check)
{
    status stat;
    Route *route;
    int i, len = list->nelts;

    for (i = 1; i <= len; i++)
    {
        stat = nthInList(list, i, (void *)&route);
        if (stat != OK)
            return 0;

        if (strcmpi(route->city->name, check->city->name) == 0)
            return route;
    }

    return 0;
}

// Puts the route information into stdout
void printRoute(void *route)
{
    printf("(%s -> %s : %dkm)", ((Route *)route)->prevCity->name, ((Route *)route)->city->name, ((Route *)route)->distFromPrev);
}
