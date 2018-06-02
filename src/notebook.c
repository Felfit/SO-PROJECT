#include "dynArrays.h"
#include <stdio.h>
#include <stdlib.h>
#include "reader.h"
#include <unistd.h>
#include <string.h>
#include "notebook.h"
#include "command.h"
#include <fcntl.h>
#include <stdio.h>

typedef struct notebook
{
    DynArray lines; //Array das linhas do ficheiro
    DynArray commands; //Array de pares (indices,comandos)
    DynArray outputs;  //Array de strigs dos outputs.
    int insertable;
}* Notebook;

/**
 *Liberta da memoria a estrutura String 
 */
void freeString(String c)
{
    if (!c)
        return;
    free(c->line);
    free(c);
    return;
}

/**
 * Devolve o numero de linhas do Notebook
 */ 
int getNumberLines(Notebook x){
    DynArray z = x->lines;
    return z->len;
}
/**
 * Coloca uma linha no Notebook, verificando se é um comando, se for chama commandDecoder.
 */ 
void insertLine(Notebook x, String l){
    if(!l)
        return;
    if(x->insertable && strcmp(">>>",l->line)==0)
        x->insertable = 0;
    if(!x->insertable){
        if(strstr(l->line,"<<<"))
            x->insertable = 1;
        freeString(l);
        return;
    }
    char * line = l->line;
    if(line[0] == '$'){
        Command c = commandDecoder(line);     
        append(x->commands,c);
    }
    append(x->lines,l);
    return;
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
        int input = c->inoffset;
        String out;
        if (input==0){
            out = execute(c,NULL);
        }
        else if(input>i)
        {
            exit(1);
        }
        else
        {
            String in = dyn_index(x->outputs, i-input);
            out = execute(c, in);
        }
        append(x->outputs,out);
    }
}
/**
 * Escreve um determindo numero de caracteres de uma linha
 */ 
void writeNChars(int fd, char *s, int N)
{
    int x = 0;
    do
    {
        int r = write(fd, s+x, N);
        if (r<0)
            exit (4);
        x += r;
    } while (x < N);
}
/**
 * Escreve uma linha no ficheiro 
 */ 
void writeLine(String s, int fd){
    writeNChars(fd,s->line,s->size); 
}

/**
 * Escreve os outputs no ficheiro
 */ 
void writeOutput(String out, int fd){
    writeNChars(fd, "\n>>>\n", 5);
    writeNChars(fd, out->line, out->size-1);
    writeNChars(fd, "<<<", 3);
}
/**
 * Reescreve o ficheiro
 */ 
void writeNotebook(Notebook x,char* filepath){
    int fd = open(filepath,O_WRONLY | O_CREAT,0644);
    int length = getNumberLines(x);
    int i,cacc = 0;
    for(i = 0;i < length;i++)
    {
        String s = dyn_index(x->lines,i);
        writeLine(s,fd);
        if(s && s->line[0] == '$'){
            String out = dyn_index(x->outputs,cacc);
            if(out)
                writeOutput(out,fd);
            cacc++;
        }
        if(i<length-1)
            writeNChars(fd, "\n", 1);
    }
}
/**
 * Inicializa a estrutura Notebook
 */ 
Notebook initNotebook(){
    Notebook r = malloc(sizeof(struct notebook));
    r->lines = initDynArray();
    r->commands = initDynArray();
    r->outputs = initDynArray();
    r->insertable=1;
    return r;
}

/**
 * Faz free da estrutura utilizada para guardar o notebook
*/

void freeNotebook(Notebook nb){
    if(nb->lines)
    for(int i = 0; i < nb->lines->len; i++){
        String str = (String) dyn_index(nb->lines, i);
        freeString(str);
    }
    freeDynArray(nb->lines);

    for(int i = 0; i < nb->outputs->len; i++){
        String str = (String) dyn_index(nb->lines, i);
        freeString(str);
    }
    freeDynArray(nb->outputs);

    for(int i = 0; i < nb->commands->len; i++){
        Command cmd = (Command) dyn_index(nb->commands, i);
        freeCommand(cmd);
    }
    freeNotebook(nb->commands);
}