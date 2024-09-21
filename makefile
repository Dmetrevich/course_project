all:prog

prog: main.o functions.o functions_print.o
	gcc -std=c99 -o prog main.o functions.o functions_print.o


main.o: main.c header.h
	gcc  -c -std=c99 -o main.o main.c

functions_print:o functions_print.c 
	gcc -c -std=c99 functions_print.c

functions:o functions.c
	gcc -c -std=c99 functions.c

clean:
	del *.o 