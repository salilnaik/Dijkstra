// Name: Salil Naik
// Project: 3
// Class: CSE 310
// Prof: Xue

#ifndef _data_structures_H
#define _data_structures_H 1

typedef struct TAG_VERTEX{
    int index;
    int color;
    double key;
    int pi;
    int position;
}VERTEX;

typedef VERTEX ELEMENT;
typedef ELEMENT *pELEMENT;
typedef struct TAG_HEAP{
    int capacity;
    int size;
    pELEMENT *H;
}HEAP;

typedef struct TAG_NODE{
    int index;
    int u;
    int v;
    double w;
    TAG_NODE *next;
}NODE;

typedef struct TAG_LISTSTACK{
    NODE *top;
    int   size;
}LISTSTACK;


#endif
