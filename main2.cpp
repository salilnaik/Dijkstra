#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "structs.h"
#include "heap.h"

int main(int argc, char **argv){
    FILE *fpr;
    FILE *fpw;
    double key;
    int returnV, position, size;
    char Word[100];
	HEAP* heap;
    if (argc < 4){
        fprintf(stderr, "Usage: %s <FileI> <FileO>\n<FileI>\tis this input file\n<FileO>\tis the output file\nflag\tis in {0, 1, 2, 3}\n", argv[0]);
        exit(0);
    }
    fpr = NULL;
    fpw = NULL;
    heap = NULL;


    while (1){
        returnV = nextInstruction(Word, &key, &position, &size);

        if (returnV == 0){
            fprintf(stderr, "Warning: Invalid instruction\n");
            continue;
        }

        if (strcmp(Word, "Stop")==0){
            fprintf(stdout, "Instruction: Stop\n");
            return 0;
        }

		if (strcmp(Word, "Init")==0){
			fprintf(stdout, "Instruction: Init %d\n", size);
		    heap = (HEAP *) calloc(1, sizeof(HEAP));
		    if (!heap){
		        fprintf(stderr, "Error: calloc failed\n");
		       	continue;
		    }
		    heap->capacity = size;
		    heap->size = 0;
		    heap->H = (ELEMENT**) calloc(size, sizeof(ELEMENT*));
		    if(!heap->H){
		        fprintf(stderr, "Error: calloc failed\n");
				free(heap);
				continue;
		    }
		}

        if (strcmp(Word, "Print")==0){
            fprintf(stdout, "Instruction: Print\n");
            if(!heap){
            	fprintf(stderr, "Error: heap is NULL\n");
            	continue;
            }
            fprintf(stdout, "%d\n", heap->size);
            int i;
            for(i=0; i<(heap->size); i++){
            	fprintf(stdout, "%lf\n", heap->H[i]->key);
            }
            continue;
        }


        if (strcmp(Word, "Write")==0){
        	fprintf(stdout, "Instruction: Write\n");
        	if(!heap){
        		fprintf(stderr, "Error: heap is NULL\n");
        		continue;
        	}
            fpw = fopen(argv[2], "w");
            if (!fpw){
                fprintf(stderr, "Error: cannot open file %s\n", argv[2]);
                continue;
            }
            fprintf(fpw, "%d\n", heap->size);
            int i;
            for(i=0; i<heap->size; i++){
            	fprintf(fpw, "%lf\n", heap->H[i]->key);
            }
            fclose(fpw);
            continue;
        }


        if (strcmp(Word, "Read")==0){
        	fprintf(stdout, "Instruction: Read\n");
        	if(!heap){
        		fprintf(stderr, "Error: heap is NULL\n");
        		continue;
        	}
        	fpr = fopen(argv[1], "r");
        	if(!fpr){
        		fprintf(stderr, "Error: cannot open file %s\n", argv[2]);
        		continue;
        	}
        	fscanf(fpr, "%d", &size);
        	if(heap->capacity < size){
        		fprintf(stderr, "Error: size %d too big for heap of capacity %d\n", size, heap->capacity);
        		continue;
        	}
        	double pIn;
        	int i;
        	ELEMENT* e;
        	for(i=0; i<size; i++){
        		fscanf(fpr, "%lf", &pIn);
        		e = (ELEMENT*) calloc(1, sizeof(ELEMENT));
        		e->key = pIn;
        		heap->H[i] = e;
        		heap->size++;
        	}
        	fclose(fpr);
        	if(!isMinHeap(heap)){
        		int calls = buildHeap(heap);
        		if(atoi(argv[3]) == 1 || atoi(argv[3]) == 3){
        			fprintf(stdout, "Input array is NOT a MinHeap\nCall BuildHeap\nNumber of Heapify calls triggered by BuildHeap: %d\n", calls-1);
        		}
        	}
        	continue;
        }

        if(strcmp(Word, "Insert")==0){
        	fprintf(stdout, "Instruction: Insert %lf\n", key);
        	if(!heap){
        		fprintf(stderr, "Error: heap is NULL\n");
        		continue;
        	}
        	if(heap->size >= heap->capacity){
        		fprintf(stderr, "Error: heap is full\n");
        		continue;
        	}
        	int pos = insert(heap, key);
        	if(atoi(argv[3]) == 2 || atoi(argv[3]) == 3){
        		fprintf(stdout, "Element with key %lf inserted at location %d of the heap array\n", key, pos+1);
        	}
        	if(atoi(argv[3]) == 0 || atoi(argv[3]) == 1){
        		fprintf(stdout, "Element with key %lf inserted into the heap\n", key);
        	}
        	continue;
        }

		if(strcmp(Word, "ExtractMin")==0){
			fprintf(stdout, "Instruction: ExtractMin\n");
			if(!heap){
        		fprintf(stderr, "Error: heap is NULL\n");
        		continue;
			}
			if(heap->size <= 0){
        		fprintf(stderr, "Error: heap is empty\n");
        		continue;
			}
			int count = 0;
			ELEMENT* e;
			e = extractMin(heap, &count);
			if(atoi(argv[3]) == 1 || atoi(argv[3]) == 3){
				fprintf(stdout, "Element with key %lf extracted from heap\nNumber of Heapify calls triggered by ExtractMin: %d\n", e->key, count);
			}
			if(atoi(argv[3]) == 0 || atoi(argv[3]) == 2){
				fprintf(stdout, "Element with key %lf extracted from heap\n", e->key);
			}
			continue;
		}

		if(strcmp(Word, "DecreaseKey")==0){
			fprintf(stdout, "Instruction: DecreaseKey %d %lf\n", position, key);
			if(!heap){
	       		fprintf(stderr, "Error: heap is NULL\n");
				continue;
			}
			if(heap->size <= 0){
        		fprintf(stderr, "Error: heap is empty\n");
				continue;
			}
			if(position >= heap->size || key >= heap->H[position]->key){
				fprintf(stderr, "Error: invalid call to DecreaseKey\n");
				continue;
			}
			decreaseKey(heap, position, key);
			continue;
		}
    }

    return 1;
}
