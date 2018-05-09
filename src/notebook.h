#ifndef __NOTEBOOK_H__
#define __NOTEBOOK_H__

#include "reader.h"

typedef struct notebook *Notebook;

void writeOutput(String out, int fd);
Notebook initNotebook();

#endif