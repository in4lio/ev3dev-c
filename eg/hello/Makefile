all: hello.o
	gcc hello.o -lev3dev-c -o hello

hello.o: hello.c
	gcc -c hello.c -I.

clean:
	rm -f *.o
	rm hello
