.PHONY: default, test

default: program

libnumber.so: number.c number.h
	gcc -c -o number.o -fPIC number.c
	gcc -o libnumber.so -shared number.o

program.o: program.c number.h
	gcc -c -o program.o -fPIC program.c

program: program.o libnumber.so
	gcc -o program program.o -lnumber -L.

clean:
	rm -f *.o

distclean: clean
	rm -f libnumber.so program
