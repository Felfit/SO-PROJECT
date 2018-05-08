#include "notebook.h"
#include "reader.h"
#define MAX_SIZE 1024

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

/**
 * Le coisas de um array
 * Passa linhas na estrutura String ao Notebook
 *
*/
void readfromFile(Notebook a, char *filepath){ //notebook a
  int fd, n=0;
    if((fd = open(filepath, O_RDONLY, 0644)) > 0){
      while(n >= 0){
        //falta meter para só pegar no que começa por $ !!!!!
        //posso fazer um read aqui para não ter de mandar NULL ou então retorno NULL na readln
        String tmp = readln(fd, &n, MAX_SIZE);
        //enviar para notebook
          printf("%s\n",tmp->line);
    }
  }
    else perror("Can't open this file!");
}
