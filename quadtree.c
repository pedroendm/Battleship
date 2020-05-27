#include "quadtree.h"

#include <stdlib.h>
#include <stdio.h>


static QuadNode* new_QuadNode(Cell* cell, int x, int y) {
    QuadNode* newNode = (QuadNode*) malloc(sizeof(QuadNode));
    newNode->cell = cell;
    newNode->x = x;
    newNode->y = y;
    for(int i = 0; i < 4; i++)
        newNode->quadrants[i] = NULL;
    return newNode;
}

static QuadNode* insertAux(QuadNode* qn, Cell* cell, int x, int y) {
    if(qn == NULL) {
        QuadNode* newNode = new_QuadNode(cell, x, y);
        return newNode;
    }

    if(x >= qn->x && y >= qn->y)
        qn->quadrants[0] = insertAux(qn->quadrants[0], cell, x, y);
    else if(x <= qn->x && y >= qn->y)
        qn->quadrants[1] = insertAux(qn->quadrants[1], cell, x, y);
    else if(x <= qn->x && y <= qn->y)
        qn->quadrants[2] = insertAux(qn->quadrants[2], cell, x, y);
    else if(x >= qn->x && y <= qn->y)
        qn->quadrants[3] = insertAux(qn->quadrants[3], cell, x, y);
    return qn;
}

QuadTree* new_QuadTree()
{
    QuadTree* qt = (QuadTree*) malloc(sizeof(QuadTree));
    return qt;
}

void insert_QuadTree(QuadTree* qt, Cell* cell, int x, int y) {
    qt->root = insertAux(qt->root, cell, x, y);
}

static void searchAux(QuadNode* qn, Cell** cell_found, int x, int y) {
    if(qn == NULL)
        return;

    if(qn->x == x && qn->y == y) {
        *cell_found = qn->cell;
        return;
    }

    for(int i = 0; i < 4; i++)
        searchAux(qn->quadrants[i], cell_found, x, y);
}

void search_QuadTree(QuadTree* qt, Cell** cell_found, int x, int y) {
    searchAux(qt->root, cell_found, x, y);
}

bool hasCellAux(QuadNode* qn, int x, int y)
{
    if(qn == NULL) return false;
    if(qn->x == x && qn->y == y) return true;

    return hasCellAux(qn->quadrants[0], x, y) || hasCellAux(qn->quadrants[1], x, y) || 
    hasCellAux(qn->quadrants[2], x, y) || hasCellAux(qn->quadrants[3], x, y);
}

bool hasCell_QuadTree(QuadTree* qt, int x, int y)
{
    return hasCellAux(qt->root, x, y);
}

void freeAux(QuadNode* qn) {
    if(qn == NULL) return;
    for(int i = 0; i < 4; i++)
        freeAux(qn->quadrants[i]);
    free(qn);
}

void free_QuadTree(QuadTree* qt)
{
    freeAux(qt->root);
}