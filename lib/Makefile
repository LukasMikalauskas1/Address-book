CFLAGS = -Wall -Werror -fPIC
LIBFLAG = -shared

BUILD_DIR = ../build
LIB_DIR = ../lib
SRC_DIR = ../src

CFILES := $(wildcard $(LIB_DIR)/*.c)
OFILES := $(patsubst $(LIB_DIR)/%.c, $(BUILD_DIR)/%.o, $(CFILES))

LIB_NAME = $(LIB_DIR)/liblist.so

all: $(BUILD_DIR) $(LIB_NAME)
	
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIB_NAME): $(OFILES)
	@$(CC) $(LIBFLAG) -o $(LIB_NAME) $(OFILES)

clean:
	@$(RM) -rf $(BUILD_DIR) $(LIB_NAME)

.PHONY: all clean
