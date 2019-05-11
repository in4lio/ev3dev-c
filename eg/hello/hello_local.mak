all: hello.o
	arm-linux-gnueabi-gcc hello.o -lev3dev-c -o hello

hello.o: hello.c
	arm-linux-gnueabi-gcc -c hello.c -I../../source/ev3/

clean:
	-rm -f *.o
	-rm -f hello
