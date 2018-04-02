CC=gcc
CFLAGS=-Wall -g -lm -pthread
DEPS = handler.h headers/httptime.h
OBJ = handler.o httptime.o

all: LightServer

LightServer: server.c $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
	rm -f *.o

clean:
	rm -f *.o LightServer

.PHONY: clean all

