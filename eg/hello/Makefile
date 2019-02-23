ifeq ($(OS),Windows_NT)
CC = gcc
LFLAGS := -lws2_32
define remove
	cmd /c 'del /f $(subst /,\,$1)'
endef
else
CC = arm-linux-gnueabi-gcc
LFLAGS :=
define remove
	rm -f
endef
endif

all: hello.o
	$(CC) hello.o -lev3dev-c $(LFLAGS) -o hello

hello.o: hello.c
	$(CC) -c hello.c -I../../source/ev3/

clean:
	-$(call remove,*.o)
	-$(call remove,hello)
