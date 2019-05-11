all: hello.o
	gcc hello.o -lev3dev-c -lws2_32 -o hello.exe

hello.o: hello.c
	gcc -c hello.c -I../../source/ev3/

clean:
	-cmd /c 'del /f $(subst /,\,*.o)'
	-cmd /c 'del /f $(subst /,\,hello.exe)'
