all:
	@$(MAKE) -C lib all
	@$(MAKE) -C src all

clean:
	@$(MAKE) -C lib clean
	@$(MAKE) -C src clean

.PHONY: all clean
