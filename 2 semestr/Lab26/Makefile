all: main
main: main.o 26.o
	gcc main.o 26.o -o main
main.o: main.c
	gcc -c main.c
26.o: lib/26.c lib/26.h
	gcc -c lib/26.c

cleano:
	rm -rf *.o
clean:
	rm -rf *.o main