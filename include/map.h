#ifndef __map_H
#define __map_H

#include "city.h"
#include "List.h"
#include "status.h"

typedef struct Route
{
    City *city;
    int distFromStart;
    int distToGoal;
} Route;

// Read map information from a text file into the list
//  @param file the full path name of data file
//  @param list the list to store map data
//  return status the result of reading and mapping the data file
status map_file_to_list(char *, List *);

// Search the shortest route between fromCity and toCity
status search_route(List *, City *, City *, List *);

#endif
