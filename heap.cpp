// Name: Salil Naik
// Project: 3
// Class: CSE 310
// Prof: Xue

#include "data_structures.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

void heapify(HEAP* heap, int index){
	ELEMENT* temp;
	int smallest;
	int left = 2*index+1;
	int right = 2*index+2;
	if(left <= heap->size-1 && heap->H[left]->key < heap->H[index]->key){
		smallest = left;
	}else{
		smallest = index;
	}
	if(right <= heap->size-1 && heap->H[right]->key < heap->H[smallest]->key){
		smallest = right;
	}
	if(smallest != index){
		temp = heap->H[index];
		heap->H[index] = heap->H[smallest];
		heap->H[index]->position = index;
		heap->H[smallest] = temp;
		heap->H[smallest]->position = smallest;
		heapify(heap, smallest);
	}
}

int buildHeap(HEAP* heap){
	int i;
	int count = 0;
	for(i=heap->size/2; i>=0; i--){
		heapify(heap, i);
	}
	return count;
}

ELEMENT* extractMin(HEAP* heap){
	ELEMENT* min = heap->H[0];
	heap->H[0] = heap->H[heap->size-1];
	heap->size--;
	heapify(heap, 0);
	return min;
}

int decreaseKey(HEAP* heap, int i, double key){
	heap->H[i]->key = key;
	ELEMENT* temp;
	while(i>0 && heap->H[(i-1)/2]->key > heap->H[i]->key){
		temp = heap->H[i];
		heap->H[i] = heap->H[(i-1)/2];
		heap->H[i]->position = i;
		heap->H[(i-1)/2] = temp;
		i = (i-1)/2;
		heap->H[i]->position = i;
	}
	return i;
}

bool isMinHeap(HEAP* heap){
	int i;
	for(i=0; i<=(heap->size-2)/2; i++){
		if(heap->H[2*i+1]->key < heap->H[i]->key)
			return false;
		if(2*i+2 < heap->size && heap->H[2*i+2]->key < heap->H[i]->key)
			return false;
	}
	return true;
}

int insert(HEAP* heap, ELEMENT* e, double key){
	heap->size++;
	int i = heap->size-1;
	e->key = -9999.0;
	e->position = i;
	heap->H[i] = e;
	int out;
	out = decreaseKey(heap, i, key);
	return out;
}
