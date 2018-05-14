#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "dynArrays.h"
#include "notebook.h"

typedef struct command
{
    char *command;
    int inoffset;
    DynArray args;
}* Command;

void redirectOutPut();
char *getInput(int fildes);
String execute(Command comando, String input);
Command commandDecoder(char* command);
void printCommandArgs(Command command);

#endif