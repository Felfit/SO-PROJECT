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

void freeString(String c){
  if (!c) return;
  free(c->line);
  free(c);
  return;
}

void stringPrepend(String s1, String s2){
  s1->size += s2->size;
  char* n = strcat(s2->line,s1->line);
  free(s1->line);
  s1->line = n;
}

String filterBuffer(Notebook a, char* buff, int size, String prev){
  int i=0,count=0;
  while(i < size){
    if(buff[i]== '>' && count == 1){
      while(buff[i] != '<')
        i++;
      i+=5;
    }
    if(buff[i] == '\n'){
      String res = makeStr(buff + i- count, count);
      if(prev != NULL){
        stringPrepend(res,prev);
        freeString(prev);
        prev = NULL;
      }
      insertLine(a, res);
      count = 0 ;
      i++;
    }
    count++;
    i++;
  }
  if(i >= size && i > count){
    String res = makeStr(buff + i - count, count);
    return res;
  }
  if (prev){
    prev->size--;
    insertLine(a,prev);
  }
  return NULL;
}


void readfromFile(Notebook a, char *filepath){ //notebook a
  int fd, count=0, rd=1;
  char* buff = (char*)malloc(MAX_SIZE);
    if((fd = open(filepath, O_RDONLY, 0644)) > 0){
        String res = NULL;
        do
        {
          while(rd>0){
            rd = read(fd, buff, 4096);
            count+= rd;
          }
          res = filterBuffer(a, buff, count,res);
          count = 0;
        } while(res != NULL);
			}
    else perror("Can't open this file!");
  close(fd);
}
