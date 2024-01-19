BUILD_DIR = build
LIB_DIR = lib
LIB_NAME = list

BUILDFLAGS = -L$(LIB_DIR) -l$(LIB_NAME) -Wl,-rpath,/usr/lib
CFLAGS = -Wall -Werror

BIN=addressbook

buildall: $(BIN) 

$(BIN): build 
	$(CC) $(CFLAGS) -o $@ $(BUILD_DIR)/*.o $(BUILDFLAGS)

build:
	$(MAKE) -C lib all
	$(MAKE) -C src all

install: buildall
	sudo install -m 644 $(LIB_DIR)/lib$(LIB_NAME).so /usr/lib

uninstall: clean
	sudo rm -f /usr/lib/lib$(LIB_NAME).so

clean:
	$(MAKE) -C lib clean
	rm -rf $(BIN) $(BUILD_DIR)

.PHONY: build buildall clean install uninstall