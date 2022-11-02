proyecto1: proy1.o matriz.o
	gcc -o proyecto1 proy1.o matriz.o

proy1.o: proy1.c matriz.h
	gcc -c proy1.c

matriz.o: matriz.c matriz.h
	gcc -c matriz.c

clean:
	rm -f proyecto1 *.o
