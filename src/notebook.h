#ifndef __NOTEBOOK_H__
#define __NOTEBOOK_H__

typedef struct string
{
    int size;
    char *line;
}* String;

typedef struct notebook *Notebook;

void freeString(String c); 
void writeNotebook(Notebook x,char* filepath);
Notebook initNotebook();
void insertLine(Notebook x, String l);
void cleanOutputLines(Notebook x);
void executeCommands(Notebook x);
void switchNotebooks(char* old, char* new);
void freeNotebook(Notebook nb);
#endif