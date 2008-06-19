main: main.o base.o pk.o sk.o fopen.o libimg.o descritor.o
	gcc -ggdb -ansi -pedantic -Wall -lefence -ljpeg -lgif -lpng main.o base.o pk.o sk.o fopen.o libimg.o descritor.o -o tp4

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

libimg.o: libimg.h libimg.c
	gcc -Wall -g -c libimg.c -ansi -Wall -pedantic

descritor.o: defines.h descritor.h descritor.c
	gcc -ggdb -ansi -pedantic -Wall -c descritor.c


clean:
	rm -f *.o tp3
