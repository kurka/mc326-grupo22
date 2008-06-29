main: main.o arvore.o
	gcc -ggdb -ansi -pedantic -Wall -lefence main.o arvore.o -o b+

main.o: main.c defines.h arvore.h
	gcc -ggdb -ansi -pedantic -Wall -c main.c

arvore.o: arvore.h defines.h arvore.c
	gcc -ggdb -ansi -pedantic -Wall -c arvore.c

clean:
	rm -f *.o b+
