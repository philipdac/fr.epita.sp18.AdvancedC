#include <limits.h>
#include <stdio.h>

#include "common.h"
#include "city.h"
#include "List.h"
#include "status.h"

status search_route(List *map, City *fromCity, City *toCity, List *route)
{
    if (!map || !route)
        return ERREMPTY;

    printf("Seaching for route from %s to %s\n", fromCity->name, toCity->name);

    return 0;
}
