#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
/*
#define MAX_SIZE 1024

typedef struct string
{
    int size;
    char *line;
}* String;


String makeString (char* buf, int size){
  String str = malloc(sizeof (struct string));
  str->line = (char*) malloc(size+1);
  str->line = buf+1;
  str->size = size;
  return str;
}

String readln(int fildes, int *n, int size){
	int rd=1,i=0;
	char c=' '; // ver se é preciso começar com ' '
  char* buf = (char*)malloc(MAX_SIZE);

    while(i<size && rd>0 && c!='\n'){
      rd = read(fildes, &c, 1); // lê 1 para já
        //filtrar o que não são comandos
        if(i == 0 && c!= '$') {
          if(rd <= 0) *n = -1;
          return NULL;
        }
        //passar para o buffer os caracteres ddo comando
        else{
          if (rd && c!="\n"){
            //if(i == 0) i++; // não funciona por algum motivo
            *(buf + i) = c;}
          }
        i++;
    }

    if(i == 0) return NULL; //ver este caso
    if(rd<=0) *n = -1;
    else{
      *(buf + i) = '\0'; // não é preciso, visto que temos size, mas deixo para já.
      *n = i;
    }
  String result = makeString(buf, i);
  return result;
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
*/

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
    //readfromFile(argv[1]);

return 0;
}
