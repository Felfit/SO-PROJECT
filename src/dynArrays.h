#ifndef __DYNAMIC_ARRAYS_H__
#define __DYNAMIC_ARRAYS_H__


typedef struct dynamicArray
{
    void* values;
    int len;
} * DynArray;

DynArray initDynArray();
void append(DynArray a, void *value);
void insert(DynArray a, int index, void *value);
void* dyn_index(DynArray a, int index);
void freeDynArray(DynArray x);


#endif