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
    /*
    if(argc < 2){
		  fprintf(stderr,"Use ./program <dumb_path>\n");
		  return -1;
	  }
  
    Notebook n = initNotebook();
    readfromFile(n,argv[1]);
    executeCommands(n);
    writeNotebook(n,"None.txt");
    */

    char* commands[] = {"$ ls |sort", "$ls <test.txt |sort", "$ls |sort >test2.txt", "$ls >test.txt >test2.txt",
                        "$ls |sort |anotherSort |something >>random.txt"};
    
    for(int i = 0; i < 5; i++){
        printf("/////Case - %d/////\n", i);
        Command cmd = commandDecoder(commands[i]);
        printCommand(cmd);
        printf("///////////////////\n");
    }


    return 0;
}
