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

String readln(int fildes, int *n, int size){
	int rd=1,i=0;
	char c; // ver se é preciso começar com ' '
  String result = malloc(sizeof(struct string));

    while(i<size && rd>0 && c!='\n'){
      rd = read(fildes, &c, 1); // lê 1 para já
        if (rd && c!='\n')
          result->line[i] = c;
        i++;
    }

    if(i == 0) return NULL; //ver este caso
    if(rd<0) *n = rd;
    else{
      result->line[i] = '\0'; // não é preciso, visto que temos size, mas deixo para já.
      *n = i;
    }
  result->size = i;
  return result;
}

void readfromFile( char *filepath){ //notebook a
  int fd, n=0;
    if((fd = open(filepath, O_RDONLY, 0644)) > 0){
      while(n >= 0){

        String tmp = readln(fd, &n, MAX_SIZE);
          printf("%s\n",tmp->line);
    }
  }
    else perror("Can't open this file!");
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
    //printf("ola");
    //readfromFile(argv[1]);

return 0;
}
