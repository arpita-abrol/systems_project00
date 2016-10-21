
GCC = gcc -g
run: all
	./test
all: tunez.o
	$(GCC) tunez.o -o test
music_library.o: tunez.c
	$(GCC) -c tunez.c
cleanH:
	rm *~
	rm *.o
