LIB := source/ev3
EXAMPLES := $(wildcard eg/*/.)

.PHONY: default all clean build-lib $(LIB) $(EXAMPLES)

default: all

all: build-lib $(EXAMPLES)

clean: $(LIB) $(EXAMPLES)

build-lib: $(LIB)
	$(MAKE) -C $(LIB) install
	$(MAKE) -C $(LIB) shared
	$(MAKE) -C $(LIB) shared-install

$(LIB) $(EXAMPLES):
	$(MAKE) -C $@ $(MAKECMDGOALS)
