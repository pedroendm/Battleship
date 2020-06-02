#ifndef QUADTREE_H
#define QUADTREE_H

#include "cell.h"
#include "quadtree.h"
#include "point.h"

typedef struct QuadNode {
  Point p;
  Cell* cell;
} QuadNode;

typedef struct QuadTree {
  // Boundaries
  Point topLeft;
  Point botRight;

  // Node
  QuadNode* n;

  struct QuadTree* quadrants[4]; // TL TR BL BR
} QuadTree;

QuadTree* new_QuadTree(int size);
void insert_QuadTree(QuadTree* qt, Cell* cell, int x, int y);
void search_QuadTree(QuadTree* qt, Cell** cell_found, int x, int y);
void free_QuadTree(QuadTree* qt);
bool hasCell_QuadTree(QuadTree* qt, int x, int y);
int maxDepth(QuadTree* qt);

#endif