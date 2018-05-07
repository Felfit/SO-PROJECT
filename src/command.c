typedef struct command
{
    char *command;
    char *args[];
}* Command;


/**
 * Executa um comando e retorna o input
 * Não altera o input do programa pai
 * @param comando comando a ser executado
 * @param input input para o programa a ser executado
 * @return output do programa
*/
char *execute(Command comando, char *input);

/**
 * Dá parse de um comando  
*/
Command commandDecoder(char* command);