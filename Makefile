CC=gcc 
#linux RM=rm -rf
RM=del
CFLAGS=-g

CFILES:=$(wildcard *.c)
OBJECTS:=$(patsubst %.c, %.o, $(CFILES))

BIN=main

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJECTS)
	$(CC) -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) $(BIN) $(OBJECTS)
