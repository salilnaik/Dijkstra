// Name: Salil Naik
// Project: 3
// Class: CSE 310
// Prof: Xue


#include <stdlib.h>
#include <stdio.h>
#include "data_structures.h"
#include "stack.h"

NODE* ptr;

NODE * ListStackPop(LISTSTACK *pLISTSTACK){
	if(!pLISTSTACK->top){
		return NULL;
	}
	ptr = pLISTSTACK->top;
	pLISTSTACK->top = pLISTSTACK->top->next;
	pLISTSTACK->size--;
	return ptr;
}

void ListStackPush(LISTSTACK *pLISTSTACK, int key){
	ptr = (NODE*) calloc(1, sizeof(NODE));
	ptr->index = key;
	ptr->next = pLISTSTACK->top;
	pLISTSTACK->top = ptr;
	pLISTSTACK->size++;
}