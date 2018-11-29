#include <limits.h>
#include <stdio.h>

#include "common.h"
#include "city.h"
#include "List.h"
#include "route.h"
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

    status stat;

    List *openList = newList(compareRoute, printRoute);
    List *closedList = newList(compareRoute, printRoute);

    goalLatitude = toCity->latitude;
    goalLongitude = toCity->longitude;

    Route *start = newRoute();
    if (!start)
        return ERRALLOC;

    start->city = fromCity;
    start->prevCity = 0;
    start->distFromPrev = 0;
    start->costFromStart = 0;
    start->costToGoal = INT_MAX;

    stat = addList(openList, start);
    if (stat != OK)
        return stat;

    return 0;

    while (openList->nelts > 0)
    {
        Route *current;
        // The top node in openList has lowest costToGoal
        stat = nthInList(openList, 1, (void *)&current);

        int i;
        for (i = 0; i < current->city->neighbors->nelts; i++)
        {
            Neighbor *nei;
            stat = nthInList(current->city->neighbors, i, (void *)&nei);
            if (stat != OK)
                return stat;

            City *nextCity = nei->city;

            if (nextCity != toCity)
            {
            }
            else
            {
                // Reach the destination
            }
        }

        addList(closedList, current);
    }

    return OK;
}
// status map_search1(List *map, City *fromCity, City *toCity, List *route)
// {
//     if (!map || !route)
//         return ERREMPTY;

//     City *visit, *nextCity;
//     int mapSize = lengthList(map);
//     int idx, distFromStart = 0;

//     Neighbor *neighbor;
//     int idxNeighbor, neighborQty;

//     status stat;

//     fromCity->routeNode->distFromStart = 0;
//     toCity->routeNode->distToGoal = 0;

//     for (idx = 0; idx < mapSize; idx++)
//     {
//         stat = nthInList(map, idx, &visit);
//         if (stat != OK)
//             return ERRINDEX;

//         if (visit->routeNode->distFromStart != INT_MAX) // this city is already visited
//             continue;

//         for (idxNeighbor = 0; idxNeighbor < neighborQty; idxNeighbor++)
//         {
//             stat = nthInList(visit->neighbors, idxNeighbor, &neighbor);
//             if (stat != OK)
//                 return ERRINDEX;

//             nextCity = getCityByName();
//             if (!(nextCity))
//                 return ERREMPTY;

//             if (nextCity->routeNode->distFromStart != INT_MAX) // this city is already visited
//                 continue;

//             nextCity->routeNode->distFromStart = distFromStart + nextCity->routeNode->distFromPrev;
//         }

//         // visit->routeNode->distFromStart = distFromStart +
//     }

//     return OK;
// }
