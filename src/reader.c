#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "notebook.h"
#include "reader.h"

#define MAX_SIZE 4096

String makeStr (char* buf, int c){
  String str = malloc(sizeof( struct string));
  str->line = (char*)malloc(c);
  memcpy(str->line, buf, c);
  str->line[c] = '\0';
  str->size = c;
  return str;
}

void filterBuffer(Notebook a, char* buff){
  int i=0,count=0;
  while(i == 0 || buff[i-1] != '\0'){
    if(buff[i] == '>'){
      while(buff[i] != '<')
        i++;
      i+=5;
    }
    if(buff[i] == '\n' || buff[i] == '\0'){
      String res = makeStr(buff + i- count, count);
      insertLine(a, res);
      count = 0 ;
      i++;
    }
    count++;
    i++;
  }
}


void readfromFile(Notebook a, char *filepath){ //notebook a
  int fd, count=0, rd=1;
  char* buff = (char*)malloc(MAX_SIZE);
    if((fd = open(filepath, O_RDONLY, 0644)) > 0){
        while(rd>0){
          rd = read(fd, buff, 4095);
          count+= rd;
        }
        *(buff + count) = '\0';
        filterBuffer(a, buff);
			}
    else perror("Can't open this file!");
  close(fd);
}
