#ifndef QUADTREE_H
#define QUADTREE_H

#include "cell.h"
#include "utils.h"
#include "quadtree.h"

typedef struct QuadNode {
  Cell* cell;
  int x, y;
  struct QuadNode* quadrants[4]; // NE NO SE SO
} QuadNode;

typedef struct QuadTree {
  struct QuadNode* root;
} QuadTree;

QuadTree* new_QuadTree();
void insert_QuadTree(QuadTree* qt, Cell* cell, int x, int y);
void search_QuadTree(QuadTree* qt, Cell** cell_found, int x, int y);
void free_QuadTree(QuadTree* qt);
bool hasCell_QuadTree(QuadTree* qt, int x, int y);

#endif