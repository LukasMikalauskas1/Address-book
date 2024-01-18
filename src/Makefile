CFLAGS = -Wall -Werror
BUILD_DIR = ../build
SRC_DIR = ../src
LIB_DIR = ../lib

CFILES := $(wildcard $(SRC_DIR)/*.c)
OFILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(CFILES))

BIN = main

LIB_NAME = $(wildcard lib*.so)

all: $(BIN)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BIN): $(BUILD_DIR) $(OFILES)
	@$(CC) $(CFLAGS) -o ../$@ $(OFILES) -L$(LIB_DIR) -llist -Wl,-rpath,$(realpath $(LIB_DIR))       

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $< -I$(LIB_DIR)

clean:
	@$(RM) -rf ../$(BIN) $(BUILD_DIR)

.PHONY: all clean