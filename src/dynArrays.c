#include <stdlib.h>
#include "dynArrays.h"


typedef struct realDynArray
{
    void** values;
    int len;
    int size;
}* RealDynArray;

void* index(DynArray a, int index){
    RealDynArray x = (RealDynArray) a;
    void* result = x->values[index];
    return result;
}

void insert(DynArray a, int index, void* value){
    RealDynArray x = (RealDynArray) a;
    x->values[index] = value;
}

static void increaseSize(DynArray a){
    RealDynArray x = (RealDynArray)a;
    void *oldvalues = x->values;
    int newSize = x->size * 2;
    x->values = realloc(x->values,newSize);
    x->size = newSize;
    free (oldvalues);
}

void append(DynArray a, void* value){
    RealDynArray x = (RealDynArray)a;
    if (x->len == x->size){
        increaseSize(a);
    }
    x->values[x->len++] = value;
}

DynArray initDynArray(){    
    RealDynArray x = malloc(sizeof(struct realDynArray));
    x->len = 0;
    x->size = 10;
    x->values = malloc(sizeof(void *)*x->size);
    return (DynArray)x;
}