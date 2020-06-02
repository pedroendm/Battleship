#ifndef POINT_H
#define POINT_H

typedef struct Point {
    int x, y;
} Point;

Point* new_Point(int x, int y);
void set_Point(Point* p, int x, int y);
void free_Point(Point* p);

#endif