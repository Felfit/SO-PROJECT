#include "command.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "notebook.h"
#include <sys/wait.h>
#include <math.h>

#define MAX_BUFF 1024

int skipSpaces(char* string, int* i){
	int nSpaces = 0;
	while(string[*i] && string[*i] == ' '){ 
		(*i) = (*i) + 1; nSpaces++;
	}
	return nSpaces;
}


void ifNotSpace(char* string, int* i){
	while(string[*i] && string[*i] != ' ') (*i)++;
}

int hasCommand(Command cmd){
	return cmd->args->len > 0;
}

int isNumber(char number){
	return number >= '0' && number <= '9';
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

void feedInput(int fd, String input){
	if(input)
		write(fd,input->line,input->size-1);
	close(fd);
}

String create_String_sized(int size){
	String res = malloc(sizeof(struct string));
	res->line = malloc(size);
	res->size = size;
	return res;
}

String collectOutput(int fd){
	int r; int len = 0; int size = 4096;
	char *buff = malloc(size);
	do
	{
		r = read(fd,buff+len,size-len);
		if(r>0)
			len += r;
		if(len==size){
			char* olbuff = buff;
			buff = realloc(buff,size);
			if(!buff)
				exit(-1);
			free (olbuff);
			size*=2;
		}		
	} while(r>0);
	close(fd);
	String res = create_String_sized(len+1);
	memcpy(res->line,buff,len);
	res->line[len] = '\0';
	return res;
}

int checkForErrors(int stderr){
	int out;
	String err = collectOutput(stderr);
	if(err->size > 1){
		printf("%s",err->line);
		return 1;
	}
	wait(&out);
	return out;
}

void closePipe(int p[2]){
	close(p[0]);
	close(p[1]);
}


void redirectInputOutputCommand(Command comando){
	if(comando->red_in){
		int in = open(comando->red_in, O_RDONLY, 0644);
		if(in<0)
			exit(1);
		dup2(in, 0);
	}
	if(comando->red_out){
		int permissions = O_WRONLY | O_CREAT;
		if (comando->append_out)
			permissions |= O_APPEND;
		int out = open(comando->red_out,permissions,0644);
		if(out<0)
			exit(1);
		dup2(out, 1);
	}
}

void execFilho(Command comando, int w[2], int r[2], int e[2]){
	dup2(r[1], 1);//vai escrever para este
	dup2(e[1], 2);//vai mandar erros para este
	dup2(w[0], 0);//vai ler deste
	closePipe(r);
	closePipe(w);
	closePipe(e);
	redirectInputOutputCommand(comando);
	execvp(dyn_index(comando->args, 0), (char* const*) comando->args->values);
	exit(1);
}

/**
 * Recebe uma lista de comandos
 * 
*/
void execPipeline(Command cmd ,int w[2], int r[2], int e[2])
{
	if (!cmd)
		return;
	int p[2];
	int tempIn[2];
	tempIn[0] = w[0];
	tempIn[1] = w[1];	
	while(cmd->next){
		pipe(p);
		if(!fork()){
			execFilho(cmd,tempIn,p,e);
		}
		close(p[1]);
		tempIn[0] = p[0];
		tempIn[1] = p[1];	
		cmd = cmd->next;	
	}
	if(!fork()){
		execFilho(cmd,tempIn,r,e);
	}
}

/**
 * Executa um comando e retorna o input
 * Não altera o input do programa pai
 * @param comando comando a ser executado
 * @param input input para o programa a ser executado
 * @return output do programa
*/
String execute(Command comando, String input){
	//To Do redirecionar o stderror e matar programa se algo acontecer
	int w[2], r[2], e[2];
	pipe(w); pipe(r); pipe(e);
	execPipeline(comando,w,r,e);
	close(w[0]); //pai nao le deste pipe
	close(e[1]); //pai nao escreve neste pipe
	close(r[1]); //pai nao escreve neste pipe
	feedInput(w[1],input);
	if(checkForErrors(e[0])){
		printf("Comando crashou");
		exit(-1);
	}
	String output = collectOutput(r[0]);
	return output;
}


int getInOffSet(char* command, int *i){
	int inoffset;
	int scanned = sscanf(command + (*i), "%d|", &inoffset);
	if(scanned){
		(*i) += (int) log10(inoffset) + 1;
		return inoffset;
	}
	else return 0;
}

/*
int filterCmd(Command comando, char* command){
	char buffer[MAX_BUFF];
	int j, i = 0;
	if(command[i] == '$') i++;
	while(command[i] == ' ') i++;
	if(command[i] == '|') {
		comando->inoffset = 1;
		i++;
	}

	else comando->inoffset = getInOffSet(command, &i);
	
	while(command[i] == ' ' || command[i] == '|') i++;
	for(j = 0; command[i] != '\0' && command[i] != ' '; j++, i++){
		buffer[j] = command[i];
	}

	buffer[j++] = '\0';
	char *cmdString = malloc(j);
	strcpy(cmdString, buffer);
	append(comando->args, cmdString);
	return i;
}*/

int insertCommand(Command cmd, char* command){
	if(hasCommand(cmd)){
		int len = strlen(command);
		char* newCommand = (char *)malloc(len+1);
		strcpy(newCommand, command);
		newCommand[0] = '$';
		cmd->next = commandDecoder(newCommand);
		return -1;
	}
	else{
		char buffer[MAX_BUFF];
		int i = 1, j = 0;
		int nSpaces = skipSpaces(command, & i);
		while(command[i] && command[i] != ' ')
			buffer[j++] = command[i++];
		if(j){
			buffer[j++] = '\0';
			char* newCommand = (char *)malloc(j);
			strcpy(newCommand, buffer);
			append(cmd->args, newCommand);
			return j + nSpaces;
		}
	}
	//free(newCommand);
	// não é suposto a função chegar a este ponto
	return 0;
}

int insertInputRedirect(Command cmd, char* command){
	char buffer[MAX_BUFF];
	int i, j;
	j = 0; i = 1;
	skipSpaces(command, &i);
	while(command[i] != '\0' && command[i] != ' ')
		buffer[j++] = command[i++];

	if(j) buffer[j++] = '\0';
	char* file = malloc(j);
	strcpy(file, buffer);
	if(hasCommand(cmd))
	//if(cmd->red_in) free(cmd->red_in);
		cmd->red_in = file;
	else cmd->red_out = file;
	return i;
}


int insertOutputRedirect(Command cmd, char* command){
	cmd->append_out = command[1] == '>' ? 1 : 0;
	char buffer[MAX_BUFF];
	int i, j;
	i = j = 0;
	while(command[i] != '\0' && command[i] == '>') i++;
	skipSpaces(command, & i);
	while(command[i] != '\0' && command[i] != ' ')
		buffer[j++] = command[i++];

	if(j) buffer[j++] = '\0';
	char* file = malloc(j);
	strcpy(file, buffer);
	if(hasCommand(cmd))
	//if(cmd->red_out) free(cmd->red_out);
		cmd->red_out = file;
	else cmd->red_in = file;
	return i;
}

/**
 * @returns 0 se a string é para ser adicionada aos argumentos do comando, 
 	-1 se um novo comando for inserido (pipe), e >0 se houve um redericionameto, sendo
 	este número o avanço do indice na string
 */

int addToComand(Command cmd, char* arg){
	switch(*arg){
		case '>': return insertOutputRedirect(cmd, arg);
		case '<': return insertInputRedirect(cmd, arg);
		case '|': return insertCommand(cmd, arg);
		default: return 0;
	}
	return 0;
}

void filterArgs(Command cmd, char* command, int iArgs){
	char buffer[MAX_BUFF];
	int i = 0, toReturn = 0;
	while(command[iArgs] != '\0'){
		skipSpaces(command, &iArgs);
		if(isNumber(command[iArgs])) cmd->inoffset = getInOffSet(command, &iArgs);
		toReturn = addToComand(cmd, command + iArgs);
		if(toReturn < 0) return;
		if(toReturn > 0){
			iArgs += toReturn;
			skipSpaces(command, &iArgs);
		} else{
			while(command[iArgs] != '\0' && command[iArgs] != ' '){
				buffer[i++] = command[iArgs++];
			}
			if(i){
				buffer[i++] = '\0';
				char* arg = malloc(i);
				strcpy(arg, buffer);
				append(cmd->args, arg);
				i = 0;
			}
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
	cmd->inoffset = 0;
	cmd->red_in = cmd->red_out = NULL;
	cmd->append_out = 0;
	cmd->next = NULL;
	filterArgs(cmd, command, 1);
	append(cmd->args, 0);
	return cmd;
}

void printCommandArgs(Command cmd){
	for(int i = 0; i < cmd->args->len - 1; i++)
      printf("Args: %s\n", (char*) dyn_index(cmd->args, i));
}

void printCommand(Command cmd){
	printf("{\n");
	printCommandArgs(cmd);
	printf("red_in: %s\nred_out : %s\nappend_out : %d\ninoffset: %d\nnext: %p", 
			cmd->red_in, cmd->red_out, cmd->append_out, cmd->inoffset, cmd->next);
	if(cmd->next){
		printf("\n>>>>>>>>>>>>>>>>>>>>\n");
		printCommand(cmd->next);
		printf("<<<<<<<<<<<<<<<<<<<<\n");
	}
	printf("\n}\n");
}