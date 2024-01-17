// Name: Salil Naik
// Project: 3
// Class: CSE 310
// Prof: Xue

#ifndef _graph_H
#define _graph_H 1
#include "data_structures.h"

int relax(ELEMENT* u, ELEMENT* v, double weight);
void dijkstra(VERTEX** v, NODE** adj, int s, int numV, int numE, HEAP* heap, LISTSTACK* stack);
void singlePair(VERTEX** v, NODE** adj, int s, int t, int numV, int numE, HEAP* heap, LISTSTACK* stack);

#endif