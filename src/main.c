#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include "reader.h"
#include "notebook.h"
#include "command.h"

#define MAX_SIZE 4096

/**
 * Dá parse de um notebook
 */ 
void parseNotebook (char* docname){
    Notebook n = initNotebook();
    readfromFile(n,docname);
    executeCommands(n);
    writeNotebook(n, docname);
}
/**
 * Função que faz com que um processo pai espere pelos seus filhos
 */ 
void waitForSons(int pids[], int N){
    int i = 0;
    for(i = 0;i < N;i++)
    {
        int status;
        waitpid(pids[i],&status,0);
        if(WIFEXITED(status) && WEXITSTATUS(status)==0)
            printf("Notebook %d parsed\n", i);
        else
            printf("Notebook %d %d failed parsing\n", i, WEXITSTATUS(status));
    }
}

int main(int argc,char *argv[])
{
    if(argc < 2){
		  fprintf(stderr,"Use ./program <path>\n");
		  return -1;
    }
    int i = 1;
    int pid;
    int pids[argc-1];
    do
    {
        pid = fork();
        if(!pid){
            parseNotebook(argv[i]);
        }
        else
            pids[i-1]=pid;
        i++;
    } while(i<argc && pid);
    if(pid){
        waitForSons(pids,argc-1);
    }
    return 0;
}