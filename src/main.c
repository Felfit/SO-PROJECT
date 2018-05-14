#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

//#include "reader.h"
#include "notebook.h"
//#include "command.h"

#define MAX_SIZE 4096

int main(int argc,char *argv[])
{
    //Ler do ficheiro para o documento
    //processDocument(Notebook n);
    //write docoment
    /*
    if(argc < 2){
		  fprintf(stderr,"Use ./program <dumb_path>\n");
		  return -1;
	  }*/

    Notebook n = initNotebook();
    String s = malloc(sizeof(struct string));
    s->line = malloc(10);
    strcpy(s->line,"$ls aaa");
    s->size = 10;
    insertLine(n, s);
    executeCommands(n);
    writeNotebook(n,"None");

    /*
    char* command = "$23|ls";
    Command cmd = commandDecoder(command);
    printf("offset: %d\n", cmd->inoffset);
    printf("command: %s\n", cmd->command);
    printCommandArgs(cmd);
    */

    return 0;

}
