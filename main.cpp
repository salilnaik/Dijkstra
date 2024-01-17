// Name: Salil Naik
// Project: 3
// Class: CSE 310
// Prof: Xue

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cfloat>
#include "graph.h"
#include "heap.h"
#include "stack.h"
#include "util.h"
#include "data_structures.h"
#include "main.h"

int main(int argc, char **argv){
    char Word[100];
    int returnV, source, destination;
    int lastSource, lastDestination, lastPair;
    int edgeIndex, u, v;
    int numV, numE;
    double w;
    int i;
    int stackP;
    FILE* fpr;
    VERTEX** V;
    NODE** adj;
    NODE* edge;
    NODE* p;
    LISTSTACK* stack;
    HEAP* heap;
    ELEMENT* e;
    if (argc < 3){
        fprintf(stderr, "Usage: %s <InputFile> <GraphType> <Flag>\n<InputFile>\tis the input file\n<GraphType>\tis either DirectedGraph or UndirectedGraph\n<Flag>\tis either 1 or 2\n", argv[0]);
        exit(0);
    }

    fpr = fopen(argv[1], "r");
        	if(!fpr){
        		fprintf(stderr, "Error: cannot open file %s\n", argv[2]);
                exit(0);
        	}
    fscanf(fpr, "%d %d", &numV, &numE);
    V = (VERTEX**) calloc(numV, sizeof(VERTEX*));
    for(i=0; i<numV; i++){
        V[i] = (VERTEX*) calloc(1, sizeof(VERTEX));
        V[i]->color = 0;
        V[i]->key = DBL_MAX;
        V[i]->index = i;
    }
    adj = (NODE**) calloc(numV, sizeof(NODE*));

    for(i=0; i<numE; i++){
        fscanf(fpr, "%d %d %d %lf", &edgeIndex, &u, &v, &w);
        if(strcmp(argv[3], "1") == 0){
            if(strcmp(argv[2], "DirectedGraph") == 0){
                edge = (NODE*) calloc(1, sizeof(NODE));
                edge->index = edgeIndex-1;
                edge->u = u-1;
                edge->v = v-1;
                edge->w = w;
                if(adj[u-1] != nullptr){
                    edge->next = adj[u-1];
                }
                adj[u-1] = edge;
            }else if(strcmp(argv[2], "UndirectedGraph") == 0){
                edge = (NODE*) calloc(1, sizeof(NODE));
                edge->index = edgeIndex-1;
                edge->u = u-1;
                edge->v = v-1;
                edge->w = w;
                if(adj[u-1] != nullptr){
                    edge->next = adj[u-1];
                }
                adj[u-1] = edge;

                edge = (NODE*) calloc(1, sizeof(NODE));
                edge->index = edgeIndex-1;
                edge->u = v-1;
                edge->v = u-1;
                edge->w = w;
                if(adj[v-1] != nullptr){
                    edge->next = adj[v-1];
                }
                adj[v-1] = edge;
            }else{
                fprintf(stderr, "Error in graph direction");
                exit(0);
            }
        }else if(strcmp(argv[3], "2") == 0){
            if(strcmp(argv[2], "DirectedGraph") == 0){
                edge = (NODE*) calloc(1, sizeof(NODE));
                edge->index = edgeIndex-1;
                edge->u = u-1;
                edge->v = v-1;
                edge->w = w;
                if(adj[u-1] != nullptr){
                    p = adj[u-1];
                    while(p->next != nullptr){
                        p = p->next;
                    }
                    p->next = edge;
                    edge->next = nullptr;
                }else{
                    adj[u-1] = edge;
                }
            }else if(strcmp(argv[2], "UndirectedGraph") == 0){
                edge = (NODE*) calloc(1, sizeof(NODE));
                edge->index = edgeIndex-1;
                edge->u = u-1;
                edge->v = v-1;
                edge->w = w;
                if(adj[u-1] != nullptr){
                    p = adj[u-1];
                    while(p->next != nullptr){
                        p = p->next;
                    }
                    p->next = edge;
                    edge->next = nullptr;
                }else{
                    adj[u-1] = edge;
                }

                edge = (NODE*) calloc(1, sizeof(NODE));
                edge->index = edgeIndex-1;
                edge->u = v-1;
                edge->v = u-1;
                edge->w = w;
                if(adj[v-1] != nullptr){
                    p = adj[v-1];
                    while(p->next != nullptr){
                        p = p->next;
                    }
                    p->next = edge;
                    edge->next = nullptr;
                }else{
                    adj[v-1] = edge;
                }
            }else{
                fprintf(stderr, "Error in graph direction");
                exit(0);
            }

        }else{
            fprintf(stderr, "Incorrect value entered as flag");
            exit(0);
        }
    }
    fclose(fpr);

    heap = (HEAP*) calloc(1, sizeof(HEAP));
    heap->capacity = numV;
    heap->H = (ELEMENT**) calloc(numV, sizeof(ELEMENT*));
    for(i=0; i<numV; i++){
        e = (ELEMENT*) calloc(1, sizeof(ELEMENT));
        heap->H[numV] = e;
    }
    stack = (LISTSTACK*) calloc(1, sizeof(LISTSTACK));
    

    while(1){
        returnV = nextInstruction(Word, &source, &destination);

        if (returnV == 0){
            fprintf(stderr, "Warning: Invalid instruction\n");
            continue;
        }

        if (strcmp(Word, "Stop")==0){
            return 0;
        }

        if (strcmp(Word, "PrintADJ")==0){
            for(i=0; i<numV; i++){
                edge = adj[i];
                fprintf(stdout, "ADJ[%d]:", i+1);
                while(edge != nullptr){
                    fprintf(stdout, "-->[%d %d: %4.2lf]", edge->u+1, edge->v+1, edge->w);
                    edge = edge->next;
                }
                fprintf(stdout, "\n");
            }
        }

        if (strcmp(Word, "SingleSource")==0){
            lastPair = 0;
            lastSource = source;
            dijkstra(V, adj, source-1, numV, numE, heap, stack);
            continue;
        }

        if(strcmp(Word, "SinglePair")==0){
            lastPair = 1;
            lastSource = source;
            lastDestination = destination;
            singlePair(V, adj, source-1, destination-1, numV, numE, heap, stack);
            continue;
        }

        if(strcmp(Word, "PrintLength")==0){
            if(source != lastSource || (lastPair == 1 && destination != lastDestination)){
                fprintf(stderr, "Source and dest should be the same as previous calculation\n");
                continue;
            }
            if(V[destination-1]->key == DBL_MAX){
                fprintf(stdout, "There is no path from %d to %d.\n", source, destination);
            }else{
                fprintf(stdout, "The length of the shortest path from %d to %d is: %8.2lf\n", source, destination, V[destination-1]->key);
            }
            continue;
        }

        if(strcmp(Word, "PrintPath")==0){
            if(source != lastSource || (lastPair == 1 && destination != lastDestination)){
                fprintf(stderr, "Source and dest should be the same as previous calculation\n");
                continue;
            }
            if(V[destination-1]->key == DBL_MAX){
                fprintf(stdout, "There is no path from %d to %d.\n", source, destination);
            }else{
                stackP = destination-1;
                while(stackP != source-1){
                    ListStackPush(stack, stackP);
                    stackP = V[stackP]->pi;
                }
                fprintf(stdout, "The shortest path from %d to %d is:\n", source, destination);
                fprintf(stdout, "[%d:%8.2lf]", source, V[source-1]->key);
                while(stack->size > 0){
                    stackP = ListStackPop(stack)->index;
                    fprintf(stdout, "-->[%d:%8.2lf]", stackP+1, V[stackP]->key);
                }
                fprintf(stdout, ".\n");
            }
            continue;
        }
    }
}
