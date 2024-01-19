BUILD_DIR = build
LIB_DIR = lib
LIB_NAME = list

BUILDFLAGS = -L$(LIB_DIR) -l$(LIB_NAME) -Wl,-rpath,/usr/lib
CFLAGS = -Wall -Werror

BIN=addressbook

all: $(BIN) 

build:
	$(MAKE) -C lib all
	$(MAKE) -C src all

install: install-lib install-bin

uninstall:uninstall-lib uninstall-bin

install-lib: all
	install -d /usr/lib
	install -m 644 $(LIB_DIR)/lib$(LIB_NAME).so /usr/lib
	install -d /usr/include
	install -m 644 $(LIB_DIR)/$(LIB_NAME).h /usr/include

install-bin: $(BIN)
	install -d /usr/bin
	install -m 755 $(BIN) /usr/bin

uninstall-lib:
	rm -f /usr/lib/lib$(LIB_NAME).so
	rm -f /usr/include/$(LIB_NAME).h

uninstall-bin:
	rm -f /usr/bin/$(BIN)

$(BIN): build 
	$(CC) $(CFLAGS) -o $@ $(BUILD_DIR)/*.o $(BUILDFLAGS)

clean:
	$(MAKE) -C lib clean
	rm -rf $(BIN) $(BUILD_DIR)

.PHONY: build all clean install uninstall install-lib install-bin uninstall-lib uninstall-bin

