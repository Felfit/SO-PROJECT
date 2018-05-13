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
    //Notebook n = initNotebook();
    //Ler do ficheiro para o documento
    //processDocument(Notebook n);
    //write docoment

    if(argc < 2){
		fprintf(stderr,"Use ./program <dumb_path>\n");
		return 0;
	}

    char *command = "$ls -la";
    Command cmd = commandDecoder(command);
    printf("%s\n", cmd->command );
    printCommandArgs(cmd);
    
    int pid = fork(), status;
    
    if(pid){
      wait(&status);
      int fd = open("output.txt", O_RDWR | O_CREAT);
      char* input = getInput(fd);
      if(input){
        printf("%s\n", input );

      }
    }
    else{
      redirectOutPut();
      write(1, "test\n", 5);
      execute(cmd, "odiaj");
      _exit(0);
    }
return 0;
}
