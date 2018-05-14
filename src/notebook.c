#include "dynArrays.h"
#include <stdio.h>
#include <stdlib.h>
#include "reader.h"
#include <unistd.h>
#include <string.h>
#include "notebook.h"
#include "command.h"

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
        Command c = commandDecoder(line);
        append(x->commands,c);
        printf("There Should Be a Command\n");
    }
    append(x->lines,line);
    return;
}

static int jumpOutsAndFrees(DynArray l, int startIndex){
    int i = startIndex,r = 0;
    char *line;
    while (i < l->len && !r)
    {
        String s = dyn_index(l,i);
        line = s->line;
        if (!strcmp(line, "<<<"))
            r=1;
        free(line);
        free(s);
        i++;
    }
    return i; 
}

void cleanOutputLines(Notebook x){
    DynArray l = x->lines;
    DynArray new = initDynArray();
    int i=0,len = l->len;
    while(i<len)
    {
        String s = dyn_index(l,i);
        if(!strcmp(s->line,">>>"))
            i=jumpOutsAndFrees(l,i);
        else{
            append(new,s);
            i++;
        }
    }
}

/**
 * executa os comandos no notebook
*/
void executeCommands(Notebook x){
    int i = 0;
    int length = x->commands->len;
    for(i = 0;i < length;i++)
    {
        Command c = dyn_index(x->commands,i);
        String out = execute(c,NULL);
        printf("out : %s",out->line);
        append(x->outputs,out);
    }
}

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

void writeNotebook(Notebook x,char* filepath){
    int fd = 1; // open(filepath,O_WRITE);
    int length = getNumberLines(x);
    int i,cacc = 0;
    for(i = 0;i < length;i++)
    {
        String s = dyn_index(x->lines,i);
        writeLine(s,fd);
        if(s ){
            String out = dyn_index(x->outputs,cacc);
            if(out)
                writeOutput(out,fd);
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