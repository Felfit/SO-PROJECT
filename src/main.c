#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "reader.h"
#include "notebook.h"
#include "command.h"

#define MAX_SIZE 1024

int main(int argc,char *argv[])
{
    //Ler do ficheiro para o documento
    //processDocument(Notebook n);
    //write docoment
    /*
    if(argc < 2){
		  fprintf(stderr,"Use ./program <dumb_path>\n");
		  return 0;
	  }*/
    Notebook n = initNotebook();
    String s = malloc(sizeof(struct string));
    s->line = malloc(5);
    strcpy(s->line,"$ls");
    s->size = 3;
    insertLine(n, s);
    executeCommands(n);
    writeNotebook(n,"None");
    return 0;
}
