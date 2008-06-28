main: main.o 
	gcc -ggdb -ansi -pedantic -Wall -lefence main.o -o b+

main.o: main.c arvore.h defines.h
	gcc -ggdb -ansi -pedantic -Wall -c main.c

arvore.o: arvore.h defines.h arvore.c
	gcc -ggdb -ansi -pedantic -Wall -c arvore.c

clean:
	rm -f *.o b+
