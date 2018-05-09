#ifndef __NOTEBOOK_H__
#define __NOTEBOOK_H__

typedef struct string
{
    int size;
    char *line;
}* String;

typedef struct notebook *Notebook;

void writeOutput(String out, int fd);
Notebook initNotebook();

#endif