#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "dynArrays.h"

typedef struct command
{
    char *command;
    DynArray args;
}* Command;

char *execute(Command comando, char *input);
Command commandDecoder(char* command);
void printCommandArgs(Command command);

#endif