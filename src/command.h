#ifndef __DYNAMIC_ARRAYS_H__
#define __DYNAMIC_ARRAYS_H__

typedef struct command
{
    char *command;
    char **args;
}* Command;


char *execute(Command comando, char *input);
Command commandDecoder(char* command);

#endif