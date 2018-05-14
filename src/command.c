#include "command.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUFF 1024

/**
 * Redericiona o output para o ficheiro output.txt
 * O conteúdo do ficheiro output.txt é apagado ao chamar esta funcao
 * FUNCAO USADA PARA TESTES E A SUA IMPLEMENTACAO ESTA A SER PONDERADA
*/
void redirectOutPut(){
	// atencao, sempre que abre o ficheiro, apaga tudo o que lá estava (O_TRUNC)
	int fd = open("output.txt", O_RDWR | O_CREAT | O_TRUNC , 0666);
	close(1);
	dup(fd);
	close(fd);
}


/**
 * Devolve o input da ultima instrução
 * @param fildes O ficheiro onde se encontra o input
 * @return a string com o input, NULLED terminated
*/
char *getInput(int fildes){
	int rd = 1;
	char buffer[MAX_BUFF], *input = NULL;
	rd = read(fildes, buffer, MAX_BUFF - 1);

	if(rd == MAX_BUFF - 1) write(3, "Input wasn't read proporly\n", 27);
	if(rd > 0){
		buffer[rd - 1] = '\0';
		input = malloc(rd + 1);
		strcpy(input, buffer);
	}
	return input;
}

/**
 * Executa um comando e retorna o input
 * Não altera o input do programa pai
 * @param comando comando a ser executado
 * @param input input para o programa a ser executado
 * @return output do programa
*/
char *execute(Command comando, char *input){
	execvp(comando->command, (char* const*) comando->args->values);
}


int filterCmd(Command comando, char* command){
	char buffer[MAX_BUFF];
	int j, i = 0;
	if(command[i] == '$') i++;
	for(j = 0; command[i] != '\0' && command[i] != ' '; j++, i++){
		buffer[j] = command[i];
	}
	buffer[j++] = '\0';
	char *cmdString = malloc(j);
	strcpy(cmdString, buffer);
	comando->command = cmdString;
	return i;
}

void filterArgs(Command comando, char* command, int iArgs){
	char buffer[MAX_BUFF];
	int i = 0;
	while(command[iArgs] != '\0'){
		while(command[iArgs] != '\0' && command[iArgs] == ' ') iArgs++;
		while(command[iArgs] != '\0' && command[iArgs] != ' '){
			buffer[i++] = command[iArgs++];
		}
		if(i){
			buffer[i++] = '\0';
			char* arg = malloc(i);
			strcpy(arg, buffer);
			append(comando->args, arg);
			i = 0;
		}
	}
}



/**
 * Dá parse de um comando  
*/
Command commandDecoder(char* command){
	if(*command != '$') return NULL;

	Command cmd = malloc(sizeof(struct command));
	cmd->args = initDynArray();

	int i = filterCmd(cmd, command);
	//Isto é preciso visto que o execvp ignora o primeiro elemento do array
	// porque pensa que é o nome do comando, logo, pus o nome do comando, mas é indiferente
	// o que estiver no primeiro elemento do array.
	append(cmd->args, cmd->command);
	filterArgs(cmd, command, i);
	append(cmd->args, 0);
	
	return cmd;
}

void printCommandArgs(Command cmd){
	for(int i = 1; i < cmd->args->len - 1; i++)
      printf("%s\n", (char*) dyn_index(cmd->args, i));
}