CC=gcc 
CFLAGS=-g

OBJECTS:=main.o list.o interface.o
CFILES:=main.c list.c interface.c

BIN=main

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJECTS)
	$(CC) -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(BIN) $(OBJECTS)