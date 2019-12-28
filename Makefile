CFLAGS=-Wall -g -DNDEBUG

ex22:
	cc -Wall -g -DNDEBUG -c -o ex22.o ex22.c
	cc -Wall -g -DNDEBUG ex22_main.c ex22.o -o ex22_main
all:
	cc ex1.c -o ex1 
	cc ex3.c -o ex3 
	cc ex8.c -o ex8
	cc ex9.c -o ex9
clean:
	rm -f ex1 ex3 ex8 ex9
