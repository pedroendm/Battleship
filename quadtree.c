#include "quadtree.h"

#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

static bool inBoundary(QuadTree* qt, Point* p) 
{ 
    if(p->x >= qt->topLeft.x && 
        p->x <= qt->botRight.x && 
        p->y >= qt->topLeft.y && 
        p->y <= qt->botRight.y)
        return true;
    return false;
} 

static QuadNode* new_QuadNode(Cell* cell, int x, int y) {
    QuadNode* newNode = (QuadNode*) malloc(sizeof(QuadNode));
    newNode->cell = cell;
    set_Point(&newNode->p, x, y);
    return newNode;
}


QuadTree* newAux(int x1, int y1, int x2, int y2)
{
    QuadTree* qt = (QuadTree*) malloc(sizeof(QuadTree));
    qt->n = NULL;
    for(int i = 0; i < 4; i++)
        qt->quadrants[i] = NULL;
    set_Point(&qt->topLeft, x1, y1);
    set_Point(&qt->botRight, x2, y2);
    return qt;
}

QuadTree* new_QuadTree(int size)
{
    QuadTree* qt = (QuadTree*) malloc(sizeof(QuadTree));
    qt->n = NULL;
    for(int i = 0; i < 4; i++)
        qt->quadrants[i] = NULL;
    set_Point(&qt->topLeft, 0, 0);
    set_Point(&qt->botRight, size, size);
    return qt;
}

static void insertAux(QuadTree* qt, QuadNode* qn) {
    if(!inBoundary(qt, &qn->p))
        return;
    
    if(abs(qt->topLeft.x - qt->botRight.x) <= 1 && abs(qt->topLeft.y - qt->botRight.y) <= 1) {
        if(qt->n == NULL)
            qt->n = qn;
        return;
    }

    if ((qt->topLeft.x + qt->botRight.x) / 2 >= qn->p.x) 
    { 
        // Indicates topLeftTree 
        if ((qt->topLeft.y + qt->botRight.y) / 2 >= qn->p.y) 
        { 
            if (qt->quadrants[0] == NULL)
                qt->quadrants[0] = newAux(qt->topLeft.x, qt->topLeft.y, (qt->topLeft.x + qt->botRight.x) / 2, (qt->topLeft.y + qt->botRight.y) / 2);
            insertAux(qt->quadrants[0], qn); 
        } 
        // Indicates botLeftTree 
        else
        { 
            if (qt->quadrants[2] == NULL)
                qt->quadrants[2] = newAux(qt->topLeft.x, (qt->topLeft.y + qt->botRight.y) / 2, (qt->topLeft.x + qt->botRight.x) / 2, qt->botRight.y); 
            insertAux(qt->quadrants[2], qn); 
        } 
    } 
    else
    { 
        // Indicates topRightTree 
        if ((qt->topLeft.y + qt->botRight.y) / 2 >= qn->p.y) 
        { 

            if (qt->quadrants[1] == NULL)
                qt->quadrants[1] = newAux((qt->topLeft.x + qt->botRight.x) / 2, qt->topLeft.y, qt->botRight.x, (qt->topLeft.y + qt->botRight.y) / 2); 
            insertAux(qt->quadrants[1], qn); 
        } 
  
        // Indicates botRightTree 
        else
        { 
            if (qt->quadrants[3] == NULL)
                qt->quadrants[3] = newAux((qt->topLeft.x + qt->botRight.x) / 2, (qt->topLeft.y + qt->botRight.y) / 2, qt->botRight.x, qt->botRight.y); 
            insertAux(qt->quadrants[3], qn); 
        } 
    } 
}   

void insert_QuadTree(QuadTree* qt, Cell* cell, int x, int y) {
    QuadNode* qn = new_QuadNode(cell, x, y);
    insertAux(qt, qn);
}

static void searchAux(QuadTree* qt, Cell** cell_found, Point* p) {
     // Current quad cannot contain it 
    if (!inBoundary(qt, p)) 
        return; 
  
    // We are at a quad of unit length 
    // We cannot subdivide this quad further 
    if (qt->n != NULL) {
        *cell_found = qt->n->cell;
        return; 
    } 
  
    if ((qt->topLeft.x + qt->botRight.x) / 2 >= p->x) 
    { 
        // Indicates topLeftTree 
        if ((qt->topLeft.y + qt->botRight.y) / 2 >= p->y) 
        { 
            if (qt->quadrants[0] == NULL) 
                return; 
            searchAux(qt->quadrants[0], cell_found, p); 
        } 
  
        // Indicates botLeftTree 
        else
        { 
            if (qt->quadrants[2] == NULL) 
                return; 
            searchAux(qt->quadrants[2], cell_found, p); 
        } 
    } 
    else
    { 
        // Indicates topRightTree 
        if ((qt->topLeft.y + qt->botRight.y) / 2 >= p->y) 
        { 
            if (qt->quadrants[1] == NULL) 
                return; 
            searchAux(qt->quadrants[1], cell_found, p); 
        } 
  
        // Indicates botRightTree 
        else
        { 
            if (qt->quadrants[3] == NULL) 
                return; 
            searchAux(qt->quadrants[3], cell_found, p); 
        } 
    }  
}

void search_QuadTree(QuadTree* qt, Cell** cell_found, int x, int y) {
    Point* p = new_Point(x, y);
    searchAux(qt, cell_found, p);
    free_Point(p);
}

bool hasCell_QuadTree(QuadTree* qt, int x, int y)
{
    Cell* cell_found = NULL;
    search_QuadTree(qt, &cell_found, x, y);
    if(cell_found != NULL) return true;
    return false;
}

int max(int a, int b, int c, int d) {
    if(a>=b && a>=c && a>=d)  return a;
    if(b>=a && b>=c && b>=d)  return b;
    if(c>=a && c>=b && c>=d)  return c;
    return d;
}

int maxDepth(QuadTree* qt) {
     if(qt == NULL)
        return -1;
    else {
        return 1 + max(maxDepth(qt->quadrants[0]),maxDepth(qt->quadrants[1]),maxDepth(qt->quadrants[2]),maxDepth(qt->quadrants[3]));  
    }
}

void freeAux(QuadNode* qn) {
    return;
}

void free_QuadTree(QuadTree* qt)
{
    return;
}

