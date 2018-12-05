#ifndef __map_H
#define __map_H

#include "city.h"
#include "List.h"
#include "status.h"

// Read map information from a text file into the list
//  @param file the full path name of data file
//  @param list the list to store map data
//  return status the result of reading and mapping the data file
status mapReadDataFile(char *, List *);

// An implementation of A* algorithm
// Search the route between startCity and goalCity
//  @param map the map where we perform our search
//  @param startCity the starting city
//  @param goalCity the destination city
//  @param route the result route
//  @ return status if any error occurs during the search
//  @ return OK otherwise
status mapSearch(List *, City *, City *, List *);

#endif
