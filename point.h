#ifndef POINT_H
#define POINT_H

typedef struct Point {
    int x, y;
} Point;

Point* new_Point(int x, int y);

#endif