#include "List.h"
#include "status.h"

// Read map information from a text file into the list
//  @param file the full path name of data file
//  @param list the list to store map data
//  return status the result of reading and mapping the data file
status map_file_to_list(char *, List *);