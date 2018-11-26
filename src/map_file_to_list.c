#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "city.h"
#include "List.h"
#include "status.h"

status map_file_to_list(char *file, List *map)
{
    FILE *fp;
    char name[MAX_CITY_NAME_LENGTH];
    int num1 = INT_MAX, num2 = INT_MAX;
    City *city = NULL;

    fp = fopen(file, "r");
    if (!fp)
        return ERROPEN;

    status result = OK;

    while (fscanf(fp, "%s %d %d", name, &num1, &num2) != EOF)
    {
        printf("name %s, num1 %d, num2 %d\n", name, num1, num2);
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
        else
        {
            // Found a neighbor line without city line in advanced --> invalid data
            if (!city)
            {
                result = ERRUNABLE;
                break;
            }

            // Neighbor info
            if (!newNeighbor(city, name, num1))
            {
                result = ERRALLOC;
                break;
            }
        }

        num1 = INT_MAX;
        num2 = INT_MAX;
    }

    fclose(fp);

    return result;
}