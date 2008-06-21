main: main.o 
	gcc -ggdb -ansi -pedantic -Wall -lefence main.o -o b+

main.o: main.c defines.h
	gcc -ggdb -ansi -pedantic -Wall -c main.c


clean:
	rm -f *.o b+
