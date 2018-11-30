#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "route.h"

int getCostToGoal(City *city, City *goalCity)
{
    int gap1 = city->latitude - goalCity->latitude;
    int gap2 = city->longitude - goalCity->longitude;
    int cost = gap1 * gap1 + gap2 * gap2;

    return sqrt(cost);
}

// Allocate memory for a route struct
//  @param city the city that the route reaches
//  @param prevRoute the previous route
//  @param distance the distance from previous city to this city
//  @param cost the cost from start city to this city
//  @return an pointer of empty route if memory allocation OK
//  @return 0 otherwise
Route *newFoundRoute(City *city, Route *prevRoute, int distance, int cost)
{
    Route *route = malloc(sizeof(Route));
    if (!route)
        return 0;

    route->city = city;
    route->prevRoute = prevRoute;
    route->distFromPrev = distance;
    route->costFromStart = cost;
    route->costToGoal = INT_MAX;

    return route;
}

// Allocate memory for a route struct
//  @param city the city that the route reaches
//  @param prevRoute the previous route
//  @param distance the distance from previous city to this city
//  @param cost the cost from start city to this city
//  @param goalCity the destination city for calculation the costToGoal
//  @return an pointer of empty route if memory allocation OK
//  @return 0 otherwise
Route *newRoute(City *city, Route *prevRoute, int distance, int cost, City *goalCity)
{
    Route *route = malloc(sizeof(Route));
    if (!route)
        return 0;

    route->city = city;
    route->prevRoute = prevRoute;
    route->distFromPrev = distance;
    route->costFromStart = cost;
    route->costToGoal = getCostToGoal(city, goalCity);

    return route;
}

// Compare route to route by total cost to have the better one
//  @param r1 the pointer to the route 1
//  @param r2 the pointer to the route 2
//  @return int as the differences between the two costToGoal
int preferLowerTotalCost(void *r1, void *r2)
{
    return ((Route *)r1)->costFromStart + ((Route *)r1)->costToGoal - ((Route *)r2)->costFromStart - ((Route *)r2)->costToGoal;
}

// The later route is always < previous route, so that it pop out earlier
//  @param r1 the pointer to the route 1
//  @param r2 the pointer to the route 2
int LIFO(void *r1, void *r2)
{
    return -1;
}

// Free memory allocated to a route
void delRoute(void *route)
{
    if (!route)
        free(route);
}

// Check if the route existed in the provided list
//  @param list the list of routes
//  @param check the route that need to be checked
//  @param revertedCheck the route is checking in the reverted way, from city back to prevCity
//  @return pointer of the route found in list
//  @return 0 if not found
Route *isRouteInList(List *list, Route *check, int revertedCheck)
{
    status exitCode;
    Route *route;
    int i, len = list->nelts;

    for (i = 1; i <= len; i++)
    {
        exitCode = nthInList(list, i, (void *)&route);
        if (exitCode != OK)
            return 0;

        if (revertedCheck)
        {
            int cityMatched = check->prevRoute && (strcmpi(route->city->name, check->prevRoute->city->name) == 0);
            int prevCityMatched = route->prevRoute && (strcmpi(route->prevRoute->city->name, check->city->name) == 0);
            if (cityMatched && prevCityMatched)
                return route;
        }
        else
        {
            int cityMatched = strcmpi(route->city->name, check->prevRoute->city->name) == 0;
            int prevCityMatched = (route->prevRoute == 0 && check->prevRoute == 0) || ((route->prevRoute && check->prevRoute && strcmpi(route->prevRoute->city->name, check->prevRoute->city->name) == 0));
            if (cityMatched && prevCityMatched)
                return route;
        }
    }

    return 0;
}

// Puts the route information into stdout
void printRoute(void *route)
{
    if (((Route *)route)->prevRoute && ((Route *)route)->city)
        printf("(%s -> %s : %d km; from start = %d km)", ((Route *)route)->prevRoute->city->name, ((Route *)route)->city->name, ((Route *)route)->distFromPrev, ((Route *)route)->costFromStart);
}
