#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "city.h"
#include "List.h"
#include "status.h"

status mapReadDataFile(char *file, List *map)
{
    FILE *fp;
    char name[MAX_CITY_NAME_LENGTH];
    int num1 = INT_MAX, num2 = INT_MAX;
    City *city, *cityAsNeighbor;

    fp = fopen(file, "r");
    if (!fp)
        return ERROPEN;

    status result = OK;

    // First read: city data
    while (fscanf(fp, "%s %d %d", name, &num1, &num2) != EOF)
    {
        // An empty row
        if (!strlen(name))
            continue;
        // num1 has no value --> invalid data
        if (num1 == INT_MAX)
        {
            result = ERRUNABLE;
            break;
        }

        if (num2 != INT_MAX)
        {
            // City info
            city = newCity();
            if (!city)
            {
                result = ERRALLOC;
                break;
            }

            setCityInfo(city, name, num1, num2);
            addList(map, city);
        }

        num1 = INT_MAX;
        num2 = INT_MAX;
    }

    // Rewind the file pointer to BOF
    rewind(fp);

    Neighbor *neighbor;

    // Second read: neighbor data
    while (fscanf(fp, "%s %d %d", name, &num1, &num2) != EOF)
    {
        // An empty row
        if (!strlen(name))
            continue;
        // num1 has no value --> invalid data: this situation already trap in the first loop

        if (num2 != INT_MAX)
        {
            city = getCityByName(map, name);
        }
        else
        {
            cityAsNeighbor = getCityByName(map, name);
            if (!cityAsNeighbor)
            {
                result = ERRABSENT;
                break;
            }

            // Neighbor info
            neighbor = newNeighbor(cityAsNeighbor, num1);
            if (!neighbor)
            {
                result = ERRALLOC;
                break;
            }

            addList(city->neighbors, neighbor);
        }

        num1 = INT_MAX;
        num2 = INT_MAX;
    }

    fclose(fp);

    return result;
}