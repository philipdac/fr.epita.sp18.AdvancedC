#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "string_ext.h"
#include "vertex.h"

// Allocate memory for a vertex struct
//  @param prevVertex the previous vertex
//  @param city of the vertex
//  @param cost from previous city to this city
//  @param cost from start city to this city
//  @param estimated cost from this city to goal city
//  @return an pointer of empty vertex if memory allocation OK
//  @return 0 otherwise
Vertex *newVertex(Vertex *prevVertex, City *city, int costFromPrev, int costFromStart, int costToGoal)
{
    Vertex *vertex = malloc(sizeof(Vertex));
    if (!vertex)
        return 0;

    vertex->city = city;
    vertex->prevVertex = prevVertex;
    vertex->costFromPrev = costFromPrev;
    vertex->costFromStart = costFromStart;
    vertex->costToGoal = costToGoal;

    return vertex;
}

// Estimate cost from a city to goal as Manhattan distance
//  @param city the first point
//  @param goalCity the second point
//  @return the calculation result
int estimateCostToGoal(City *city, City *goalCity)
{
    int gap1 = abs(city->posX - goalCity->posX);
    int gap2 = abs(city->posY - goalCity->posY);

    return (gap1 + gap2) / 4;
}

// Compare vertex to vertex by total cost (actual cost from start + estimated cost to goal)
//  @param r1 the pointer to the vertex 1
//  @param r2 the pointer to the vertex 2
//  @return int as the differences between the two costToGoal
int compareTotalCost(void *r1, void *r2)
{
    int totalCost1 = ((Vertex *)r1)->costFromStart + ((Vertex *)r1)->costToGoal;
    int totalCost2 = ((Vertex *)r2)->costFromStart + ((Vertex *)r2)->costToGoal;

    return totalCost1 - totalCost2;
}

// Compare vertex to vertex by city name
//  @param vertex1 the pointer to the vertex1
//  @param vertex2 the pointer to the vertex2
//  return int as the result of strcpm_insensitive
int compareByCityName(void *vertex1, void *vertex2)
{
    return strcpm_insensitive(((Vertex *)vertex1)->city->name, ((Vertex *)vertex2)->city->name);
}

// The later vertex is always < previous vertex, so that it pop out earlier
//  @param r1 the pointer to the vertex 1
//  @param r2 the pointer to the vertex 2
int LIFO(void *r1, void *r2)
{
    return -1;
}

// Free memory allocated to a vertex
void delVertex(void *vertex)
{
    if (!vertex)
        free(vertex);
}

// Check if the vertex existed in the provided list
//  @param list the list of vertex
//  @param vertex the vertex need to be checked
//  @return pointer of the vertex found in list
//  @return 0 if not found
Vertex *isVertexInList(List *list, Vertex *vertex)
{
    status exitCode;
    Vertex *inList;
    int i, len = list->nelts;

    for (i = 1; i <= len; i++)
    {
        exitCode = nthInList(list, i, (void *)&inList);
        if (exitCode != OK)
            return 0;

        int found = strcmp(vertex->city->name, inList->city->name) == 0;
        if (found)
            return inList;
    }

    return 0;
}

// Puts the vertex information into stdout
void printVertex(void *vertex)
{
    if (((Vertex *)vertex)->prevVertex)
        printf("%s -> %s : %d km. Distance from start = %d km\n",
               ((Vertex *)vertex)->prevVertex->city->name,
               ((Vertex *)vertex)->city->name,
               ((Vertex *)vertex)->costFromPrev,
               ((Vertex *)vertex)->costFromStart);
    else
        printf("\n"); // starting point
}
