#include "dynArrays.h"
#include <stdio.h>
#include <stdlib.h>
#include "reader.h"
#include <unistd.h>

#include "notebook.h"


typedef struct notebook
{
    DynArray lines; //Array das linhas do ficheiro
    DynArray commands; //Array de pares (indices,comandos)
    DynArray outputs;  //Array de strigs dos outputs.
}* Notebook;

int getNumberLines(Notebook x){
    DynArray z = x->lines;
    return z->len;
}

void insertLine(Notebook x, String l){
    if(!l)
        return;
    char * line = l->line;
    if(line[0] == '$'){
        //Command c - Interpertador de comandos
        //append(x->commands,c);
        printf("There Should Be a Command\n");
    }
    append(x->lines,line);
    return;
}

/**
 * executa os comandos no notebook
*/
void processDocument(Notebook x);

void writeLine(String s, int fd){
    write(fd,s->line,s->size);
    write(fd,"\n",1);
}

void writeOutput(String out, int fd){
    write(fd, ">>>\n", 4);
    write(fd, out->line, out->size);
    write(fd, "\n", 1);
    write(fd, "<<<\n", 4);
}

void writeDocument(Notebook x,char* filepath){
    int fd = 1; // open(filepath,O_WRITE);
    int length = getNumberLines(x);
    int i,cacc = i = 0;
    for(i = 0;i < length;i++)
    {
        String s = dyn_index(x->lines,i);
        writeLine(s,fd);
        if(s->line[0]=='$'){
            writeOutput(s,fd);
            cacc++;
        }
    }
}

Notebook initNotebook(){
    Notebook r = malloc(sizeof(struct notebook));
    r->lines = initDynArray();
    r->commands = initDynArray();
    r->outputs = initDynArray();
    return r;
}