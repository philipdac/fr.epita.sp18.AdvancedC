#include <limits.h>
#include <stdio.h>

#include "common.h"
#include "city.h"
#include "List.h"
#include "status.h"
#include "vertex.h"

status linkFoundVertex(List *route, Vertex *finalVertex)
{
    status exitCode;
    Vertex *vertex = finalVertex;

    while (1)
    {
        Vertex *found = newVertex(vertex->prevVertex, vertex->city, vertex->costFromPrev, vertex->costFromStart, -1);
        exitCode = addList(route, found);
        if (exitCode != OK)
            return exitCode;

        vertex = vertex->prevVertex;
        if (!vertex)
            return OK;
    }
}

int isVertexOpenable(List *openList, List *closedList, Vertex *vertex)
{
    Vertex *inList;

    // vertex existed in openList?
    inList = isVertexInList(openList, vertex);
    if (inList)
    {
        if ((inList->costFromStart) > (vertex->costFromStart))
            // Route thru this vertex is shorter and need to be considered
            return -1;
        else
            // Route thru this vertext is longer --> can be ignored
            return 0;
    }

    // vertex existed in closedList?
    inList = isVertexInList(closedList, vertex);
    if (!inList)
        // A new vertex
        return -1;

    if ((inList->costFromStart) > (vertex->costFromStart))
    {
        // This vertex was visited but the new route is shorter --> reconsidered
        return -1;
    }

    return 0;
}

void freeMemMapSearch(List *openList, List *closedList)
{
    forEach(openList, delVertex);
    delList(openList);

    forEach(closedList, delVertex);
    delList(closedList);
}

// An implementation of A* algorithm
// Search the route between startCity and goalCity
//  @param map the map where we perform our search
//  @param startCity the starting city
//  @param goalCity the destination city
//  @param route the result route
//  @ return status if any error occurs during the search
//  @ return OK otherwise
status mapSearch(List *map, City *startCity, City *goalCity, List *route)
{
    if (!map || !route)
        return ERREMPTY;

    status exitCode;

    List *openList = newList(compareTotalCost, printVertex);

    // LIFO is the nature of a stack. Function LIFO does not compare anything.
    // Just use this function for better running speed vs. other comparision function
    List *closedList = newList(compareByCityName, printVertex);
    if (!openList || !closedList)
        return ERRALLOC;

    Vertex *current, *next;
    Vertex *first = newVertex(0, startCity, 0, 0, INT_MAX);
    if (!first)
    {
        freeMemMapSearch(openList, closedList);
        return ERRALLOC;
    }

    exitCode = addList(openList, first);
    if (exitCode != OK)
    {
        freeMemMapSearch(openList, closedList);
        return exitCode;
    }

    int found = 0;
    while (openList->nelts > 0)
    {
        // The current vertex in openList has lowest costToGoal
        // Pop it out for processing
        exitCode = remFromListAt(openList, 1, (void *)&current);
        if (exitCode != OK)
        {
            freeMemMapSearch(openList, closedList);
            return exitCode;
        }

        // Break the while loop if it reaches the goal
        if (current->city == goalCity)
        {
            found = -1;
            break;
        }

        exitCode = addList(closedList, current);
        if (exitCode != OK)
        {
            freeMemMapSearch(openList, closedList);
            return exitCode;
        }

        int i;
        for (i = 1; i <= current->city->neighbors->nelts; i++)
        {
            Neighbor *nei;
            exitCode = nthInList(current->city->neighbors, i, (void *)&nei);
            if (exitCode != OK)
            {
                freeMemMapSearch(openList, closedList);
                return exitCode;
            }

            next = newVertex(current, nei->city, nei->distance, nei->distance + current->costFromStart, estimateCostToGoal(nei->city, goalCity));

            if (isVertexOpenable(openList, closedList, next))
            {
                addList(openList, next);
            }
        }
    }

    if (found)
        exitCode = linkFoundVertex(route, current);
    else
        // Not found: run until openList is empty but can't reach the goal city
        exitCode = OK;

    freeMemMapSearch(openList, closedList);

    return exitCode;
}
