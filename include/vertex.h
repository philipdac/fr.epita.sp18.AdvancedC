#ifndef __vertex_H
#define __vertex_H

#include "city.h"
#include "List.h"
#include "status.h"

typedef struct Vertex
{
    struct City *city;
    struct Vertex *prevVertex;
    int costFromPrev;
    int costFromStart;
    int costToGoal;
} Vertex;

// Allocate memory for a vertex struct
//  @param prevVertex the previous vertex
//  @param city of the vertex
//  @param cost from previous vertext to this vertext
//  @param cost from start vertext to this vertext
//  @param estimated cost from this vertext to goal vertext
//  @return an pointer of empty vertex if memory allocation OK
//  @return 0 otherwise
Vertex *newVertex(Vertex *, City *, int, int, int);

// Estimate cost to goal as Manhattan distance
//  @param city the first point
//  @param goalCity the second point
//  @return the calculation result
int estimateCostToGoal(City *, City *);

// Compare vertex to vertex by total cost (actual cost from start + estimated cost to goal)
//  @param r1 the pointer to the vertex 1
//  @param r2 the pointer to the vertex 2
//  return int as the result of costToGoal1 - costToGoal2
int compareTotalCost(void *, void *);

// Compare vertex to vertex by city name
//  @param vertex1 the pointer to the vertex1
//  @param vertex2 the pointer to the vertex2
//  return int as the result of strcpm_insensitive
int compareByCityName(void *, void *);

// The later vertex is always < previous vertex, so that it pop out earlier
//  @param r1 the pointer to the vertex 1
//  @param r2 the pointer to the vertex 2
int LIFO(void *, void *);

// Check if the vertex existed in the provided list
//  @param list the list of vertex
//  @param city the city of vertex
//  @return pointer of the vertex found in list
//  @return 0 if not found
Vertex *isVertexInList(List *, Vertex *);

// Free memory allocated to a vertex
void delVertex(void *);

// Puts the vertex information into stdout
void printVertex(void *);

#endif
