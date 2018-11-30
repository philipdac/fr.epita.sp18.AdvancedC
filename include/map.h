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

// Search the shortest route between fromCity and toCity
//  @param map the map where we perform our search
//  @param fromCity the starting city
//  @param toCity the destination city
//  @param route the result route
//  @ return ERRINDEX if any error occurs during the search
//  @ return OK otherwise
status mapSearch(List *, City *, City *, List *);

#endif
