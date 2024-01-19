BUILD_DIR = ../build
SRC_DIR = ../src
LIB_DIR = ../lib

CFILES := $(wildcard $(SRC_DIR)/*.c)
OFILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(CFILES))

LIB_NAME = $(wildcard lib*.so)

CFLAGS = -Wall -Werror

all: $(BUILD_DIR) $(OFILES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I$(LIB_DIR)

clean:
	$(RM) -rf $(BUILD_DIR)

.PHONY: all clean