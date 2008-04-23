main: main.o base.o pk.o
	gcc -ggdb -ansi -pedantic -Wall main.o base.o pk.o -o tp3

main.o: main.c base.h pk.h defines.h
	gcc -ggdb -ansi -pedantic -Wall -c main.c

base.o: base.h defines.h base.c
	gcc -ggdb -ansi -pedantic -Wall -c base.c 

pk.o: pk.h defines.h pk.c
	gcc -ggdb -ansi -pedantic -Wall -c pk.c

clean:
	rm -f *.o tp3
