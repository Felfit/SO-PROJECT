#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "reader.h"
#include "notebook.h"
#include "command.h"

#define MAX_SIZE 4096

int main(int argc,char *argv[])
{
    if(argc < 2){
		  fprintf(stderr,"Use ./program <dumb_path>\n");
		  return -1;
	  }
  
    /*
    Notebook n = initNotebook();
    readfromFile(n,argv[1]);
    executeCommands(n);
    writeNotebook(n,"None");
    writeNotebook(n,"test.txt");
    */
    
    char* command = "$ls -l -la";
    Command cmd = commandDecoder(command);
    printf("offset: %d\n", cmd->inoffset);
    printf("command: %s\n", cmd->command);
    printCommandArgs(cmd);
    
    return 0;
}
