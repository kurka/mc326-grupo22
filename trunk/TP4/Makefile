main: main.o base.o pk.o sk.o fopen.o 
	gcc -ggdb -ansi -pedantic -Wall -lefence main.o base.o pk.o sk.o fopen.o -o tp4
main.o: main.c base.h pk.h defines.h fopen.h
	gcc -ggdb -ansi -pedantic -Wall -c main.c

base.o: base.h defines.h base.c
	gcc -ggdb -ansi -pedantic -Wall -c base.c 

pk.o: pk.h defines.h pk.c
	gcc -ggdb -ansi -pedantic -Wall -c pk.c

fopen.o: fopen.h defines.h fopen.c
	gcc -ggdb -ansi -pedantic -Wall -c fopen.c

sk.o: sk.h defines.h sk.c
	gcc -ggdb -ansi -pedantic -Wall -c sk.c
clean:
	rm -f *.o tp3
