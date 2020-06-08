all: build

build: malloc.h malloc.c main.c
	gcc -Wall -Werror malloc.c main.c -o program

clean:
	rm -f program program.o

test: 
	valgrind --leak-check=full ./program
