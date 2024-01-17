// Name: Salil Naik
// Project: 3
// Class: CSE 310
// Prof: Xue

#include "data_structures.h"

#ifndef _heap_H
#define _heap_H 1

void heapify(HEAP* heap, int index);
int buildHeap(HEAP* heap);
ELEMENT* extractMin(HEAP* heap);
int decreaseKey(HEAP* heap, int i, double key);
bool isMinHeap(HEAP* heap);
int insert(HEAP* heap, ELEMENT* e, double key);
#endif
