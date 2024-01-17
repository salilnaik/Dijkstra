// Name: Salil Naik
// Project: 3
// Class: CSE 310
// Prof: Xue

#include <stdio.h>
#include <string.h>
#include "util.h"

int nextInstruction(char *Word, int *Source, int *Destination)
{
    int  returnV;
    int returnV1;
    fscanf(stdin, "%s", Word);
    if (strcmp(Word, "Stop")==0)   return 1;
    if (strcmp(Word, "PrintADJ")==0)  return 1;
    if (strcmp(Word, "SinglePair")==0){
        returnV = fscanf(stdin, "%d", Source);
        returnV1 = fscanf(stdin, "%d", Destination);
        if (returnV == 1 && returnV1 == 1){
            return 1;
        }else{
            return 0;
        }
    }
    if (strcmp(Word, "SingleSource")==0){
        returnV = fscanf(stdin, "%d", Source);
        if (returnV == 1){
            return 1;
        }else{
            return 0;
        }
    }
    if (strcmp(Word, "PrintLength")==0){
        returnV = fscanf(stdin, "%d", Source);
        returnV1 = fscanf(stdin, "%d", Destination);
        if (returnV == 1 && returnV1 == 1){
            return 1;
        }else{
            return 0;
        }
    }
    if (strcmp(Word, "PrintPath")==0){
        returnV = fscanf(stdin, "%d", Source);
        returnV1 = fscanf(stdin, "%d", Destination);
        if (returnV == 1 && returnV1 == 1){
            return 1;
        }else{
            return 0;
        }
    }
    return 0;
}
