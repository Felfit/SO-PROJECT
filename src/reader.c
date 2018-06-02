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

/**
 *@param c, tamanho da string
 *Cria uma estrutura String 
 */
String makeStr (char* buf, int c){
  String str = malloc(sizeof( struct string));
  str->line = (char*)malloc(c);
  memcpy(str->line, buf, c);
  str->line[c] = '\0';
  str->size = c;
  return str;
}
/**
*Concatena duas estruturas do tipo String
*/
void stringPrepend(String s1, String s2){
  s1->size += s2->size;
  char* n = strcat(s2->line,s1->line);
  free(s1->line);
  s1->line = n;
}

/**
 * @param buff, contém todas as strings do ficheiro
 * @param size, quantos caracteres leu
 * @param prev, string anterior, caso o buffer tenha cortado uma linha a meio ao chegar à sua capacidade máxima
 * Filtra o buffer recebido, retirando as respostas, e coloca uma a uma as linhas pretendidas na estrutura notebook
 */
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
    if (strlen(prev->line)) {
      insertLine(a, prev);
    }
    else  
      freeString(prev);
  }
  return NULL;
}

/**
* Lê de um ficheiro para a estrutura Notebook as todas as linhas que não correspondem a respostas de comandos
*/
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
    else {
      perror("Can't open this file!");
      exit(2);
    }
  close(fd);
}
