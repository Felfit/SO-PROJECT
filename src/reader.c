#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "notebook.h"
#include "reader.h"

#define MAX_SIZE 1024

void redirectOutputToFile(int fildes){
  close(1);
  dup(fildes);
  // ou usar a versao do dup2()
}

String readln(int fildes, int *n){
	int rd=1,i=0;
	char c=' '; // ver se é preciso começar com ' '
  String str = malloc(sizeof( struct string));
  str->line = (char*)malloc(MAX_SIZE);

    while(i<MAX_SIZE && rd>0 && c!='\n'){
      rd = read(fildes, &c, 1); // lê 1 para já
          if (rd && c!='\n'){
            str->line[i] = c;}
        i++;
    }

    if(i == 0) return NULL; //ver este caso
    if(rd<=0) *n = -1;
    else{
      str->line[i-1] = '\0';
      *n = i;
    }
  str->size = i;
  return str;
}

void readfromFile(Notebook a, char *filepath){ //notebook a
  int fd, n=0;
    if((fd = open(filepath, O_RDWR, 0644)) > 0){
      while(n >= 0){
        String tmp = readln(fd, &n);
            if(tmp){
              //mete no notebook

              int j=0;
              while(tmp->line[j]!='\0'){
                redirectOutputToFile(fd);
                writeOutput(tmp, fd);
                j++;
              }
            }
      }
    }
    else perror("Can't open this file!");
  close(fd);
}
