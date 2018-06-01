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
    switchNotebooks(argv[1], "None.txt");
    */
    
    
    char* commands[] = {"$ ls", "$| wc -l", "$2| line", "$ ls | line",
                        "$| cat >outputFile.txt", "$2| cat >>outputFile.txt", "$ cat <outputFile.txt",
                        "$ ls /bin/ | head >outputFile2.txt","$ cat <outputFile2.txt | sort -r >outputFile3.txt",
                        "$ cat <outputFile3.txt"};
    
    for(int i = 0; i < 10; i++){
        printf("/////Case - %s/////\n", commands[i]);
        Command cmd = commandDecoder(commands[i]);
        printCommand(cmd);
        printf("///////////////////\n");
    }
    

    return 0;
}
