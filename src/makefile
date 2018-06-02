CC=gcc
CFLAGS=-g -Wall -O2 -o
OBJECTS=*.c
EXEC =notebook
LYBRARIES=reader.h dynArrays.h notebook.h command.h  
LINC =-lm

notebook:
	$(CC) $(CFLAGS) $(EXEC) $(OBJECTS) $(LINC)

clean: 
	rm $(EXEC)