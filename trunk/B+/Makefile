main: main.o leitura.o insercao.o remocao.o
	gcc -ggdb -ansi -pedantic -Wall -lefence main.o leitura.o insercao.o remocao.o -o b+

main.o: main.c defines.h leitura.h insercao.h remocao.h
	gcc -ggdb -ansi -pedantic -Wall -c main.c

leitura.o: leitura.h defines.h leitura.c
	gcc -ggdb -ansi -pedantic -Wall -c leitura.c

insercao.o: insercao.h defines.h leitura.h insercao.c
	gcc -ggdb -ansi -pedantic -Wall -c insercao.c

remocao.o: remocao.h defines.h leitura.h remocao.c
	gcc -ggdb -ansi -pedantic -Wall -c remocao.c


clean:
	rm -f *.o b+
