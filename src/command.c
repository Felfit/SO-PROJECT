#include "command.h"
#include <unistd.h>
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
	execv(comando->command, comando->args);
}

/**
 * Dá parse de um comando  
*/
Command commandDecoder(char* command){
	if(*command != '$') return NULL;

	Command cmd = malloc(sizeof(struct command));
	cmd->command = NULL; 
	cmd->args = NULL;
	char buffer[MAX_BUFF];

	for(int i = 1; command[i] != '\0'; i++){
		while(command[i] != '\0' && command[i] == ' ') i++;
		int j;
		if(!cmd->command){
			for(j = 0; command[i] != '\0' && command[i] != ' '; j++, i++){
				buffer[j] = command[i];
			}
			buffer[j++] = '\0';
			char *cmdString = malloc(j);
			strcpy(cmdString, buffer);
			cmd->command = cmdString;
		}

		/*for(j = 0; command[i] != '\0' && command[i] != ' '; j++, i++){
			buffer[j] = command[i];
		}
		buffer[j++] = '\0';
		char *cmdArg = malloc(j);
		strcpy(cmdArg, buffer);
*/

	}
	return cmd;
}