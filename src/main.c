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
    //Notebook n = initNotebook();
    //Ler do ficheiro para o documento
    //processDocument(Notebook n);
    //write docoment

    if(argc < 2){
		fprintf(stderr,"Use ./program <dumb_path>\n");
		return 0;
	}
    //printf("ola");
    readfromFile(argv[1]);
/*
    char *command = "$ls -la";
    Command cmd = commandDecoder(command);
    printf("%s\n", cmd->command );
    printCommandArgs(cmd);
    execute(cmd, "odiaj");
  /*  char* la[100];
    la[0] = "-la"; la[1] = NULL;
    execvp(cmd->command, (char* const*)la);
  */
return 0;
}
