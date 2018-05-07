typedef struct dynamicArray
{
    void* values;
    int len;
} * DynArray;

DynArray initDynArray();
void append(DynArray a, void *value);
void insert(DynArray a, int index, void *value);
void* index(DynArray a, int index);