#include "command.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFF 1024

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