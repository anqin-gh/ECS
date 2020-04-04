.PHONY: all clean cleanall

all:
	
	$(MAKE) -C tinyPTC
	$(MAKE) -C picoPNG

# $(foreach DIR,$(shell find . -mindepth 1 -maxdepth 1 -type d),$(MAKE) -C $(DIR))
clean:
	$(MAKE) -C tinyPTC clean
	$(MAKE) -C picoPNG clean

cleanall:
	$(MAKE) -C tinyPTC cleanall
	$(MAKE) -C picoPNG cleanall