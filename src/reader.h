#ifndef __READER_H__
#define __READER_H__

#include "notebook.h"

typedef struct string
{
    int size;
    char *line;
}* String;

void readfromFile(Notebook a, char *filepath);

#endif