#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "reader.h"
#include "notebook.h"
#include "command.h"

#define MAX_SIZE 1024

typedef struct string
{
    int size;
    char *line;
}* String;

String readln(int fildes, int *n, int size){
	int rd=1,i=0;
  String str = malloc(sizeof( struct string));
  str->line = (char*)malloc(MAX_SIZE);
  int count=1;
    while(i<size && rd>0 && str->line[i]!='\n'){
      rd = read(fildes, &str->line, 1024); // lê 1 para já
        i++;

    }

    if(i == 0) return NULL; //ver este caso
    if(rd<=0) *n = -1;
    else{
      str->line[i] = '\0';
      *n = i;
    }
  str->size = i;
  return str;
}

void readfromFile( char *filepath){ //notebook a
  int fd, n=0;
    if((fd = open(filepath, O_RDONLY, 0644)) > 0){
      while(n >= 0){
        String tmp = readln(fd, &n, MAX_SIZE);
            if(tmp){

              int j=0;
              while(tmp->line[j]!='\0'){
                printf("%c",tmp->line[j]);
                j++;
              }
            }

    }
  }
    else perror("Can't open this file!");
  close(fd);
}


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
    //readfromFile(n, argv[1]);

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
