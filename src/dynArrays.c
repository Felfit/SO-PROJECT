#include <stdlib.h>
#include "dynArrays.h"
#include <string.h>

typedef struct realDynArray
{
    void** values;
    int len;
    int size;
}* RealDynArray;

/**
 * Devolve o valor que está no inice igual a index
 */ 
void* dyn_index(DynArray a, int index){
    RealDynArray x = (RealDynArray) a;
    void* result = x->values[index];
    return result;
}
/**
 * Insere um elemento num determinado indice
 */ 
void insert(DynArray a, int index, void* value){
    RealDynArray x = (RealDynArray) a;
    x->values[index] = value;
}
/**
 * Aumenta o tamanho da estrutura
 */ 
static void increaseSize(DynArray a){
    RealDynArray x = (RealDynArray)a;
    void **oldvalues = x->values;
    int newSize = x->size * 2;
    x->values = malloc(newSize * sizeof(void*));
    memcpy(x->values,oldvalues,sizeof(void*)*x->size);
    x->size = newSize;
    free (oldvalues);
}
/**
 * Adiciona um elemento à "cauda" do array 
 */ 
void append(DynArray a, void* value){
    RealDynArray x = (RealDynArray)a;
    if (x->len + 1 == x->size){   
        increaseSize(a);  
    }
    x->values[x->len++] = value;
}
/**
 * Inicializa o array
 */ 
DynArray initDynArray(){    
    RealDynArray x = malloc(sizeof(struct realDynArray));
    x->len = 0;
    x->size = 10;
    x->values = malloc(sizeof(void*)*x->size);
    return (DynArray)x;
}

/**
 * Faz free do array dinamico
 */
void freeDynArray(DynArray a){
    if(!a) return;
    RealDynArray x = (RealDynArray)a;
    free(x->values);
    free(x);
}