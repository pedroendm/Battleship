#include "point.h"

#include <stdlib.h>
#include "io.h"

Point* new_Point(int x, int y)
{
    Point* point = (Point*) malloc(sizeof(Point));
    if(point == NULL)
        prompt_IO(ERROR_IO, "point.c, new_Point(): malloc failed");

    point->x = x;
    point->y = y;

    return point;
}