CFLAGS = -Wall -Werror -fPIC
LIBFLAG = -shared

LIB_DIR = ../lib

CFILES := $(wildcard $(LIB_DIR)/*.c)
OFILES := $(patsubst $(LIB_DIR)/%.c, %.o, $(CFILES))

LIB_NAME = $(LIB_DIR)/liblist.so

all: $(LIB_NAME)
	
$(LIB_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_NAME): $(OFILES)
	$(CC) $(LIBFLAG) -o $(LIB_NAME) $(OFILES)

clean:
	$(RM) -rf $(LIB_NAME) $(OFILES)

.PHONY: all clean