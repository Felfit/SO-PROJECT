#include "dynArrays.h"

typedef struct notebook
{
    DynArray *lines; //Array das linhas do ficheiro
    DynArray *commands; //Array dos indices dos comandos
    DynArray *outputs;  //Array de strigs dos outputs.
}* Notebook;

void insertLine(Notebook x, char *line);
/**
 * executa os comandos no notebook
*/
void processDocument(Notebook x);
Notebook initNotebook();