// Name: Salil Naik
// Project: 3
// Class: CSE 310
// Prof: Xue

#include <cfloat>
#include <stdlib.h>
#include <stdio.h>
#include "data_structures.h"
#include "heap.h"
#include "stack.h"

int i;
int r;
ELEMENT* u;
NODE* node;
NODE* n;

int relax(ELEMENT* u, ELEMENT* v, double weight){
    if(v->key > u->key + (double)weight){
        v->key = u->key + (double)weight;
        v->pi = u->index;
        return 1;
    }
    return 0;
}


void dijkstra(VERTEX** v, NODE** adj, int s, int numV, int numE, HEAP* heap, LISTSTACK* stack){
    while(heap->size > 0){
        extractMin(heap);
    }
    for(i=0; i<numV; i++){
        if(i==s){
            insert(heap, v[s], 0.0);
        }else{
            insert(heap, v[i], DBL_MAX);
        }
    }
    while(heap->size > 0){
        node = (NODE*) calloc(1, sizeof(NODE));
        u = extractMin(heap);
        node->index = u->index;
        n = adj[u->index];
        while(n != nullptr){
            r = relax(u, v[n->v], n->w);
            if(r==1){
                decreaseKey(heap, v[n->v]->position, v[n->v]->key);
            }
            n = n->next;
        }
    }
}

void singlePair(VERTEX** v, NODE** adj, int s, int t, int numV, int numE, HEAP* heap, LISTSTACK* stack){
    while(heap->size > 0){
        extractMin(heap);
    }
    for(i=0; i<numV-1; i++){
        if(i==s){    
            insert(heap, v[s], 0.0);
        }else{
            insert(heap, v[i], DBL_MAX);
        }
    }
    while(heap->size > 0){
        node = (NODE*) calloc(1, sizeof(NODE));
        u = extractMin(heap);
        if(u==v[t]) return;
        node->index = u->index;
        // ListStackPush(stack, node);
        n = adj[u->index];
        while(n != nullptr){
            r = relax(u, v[n->v], n->w);
            if(r==1){
                decreaseKey(heap, v[n->v]->position, v[n->v]->key);
            }
            n = n->next;
        }
    }
}