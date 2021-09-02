CFLAGS=-Wall -std=c99 -pedantic -g

all: main

main: netpbm.h main.c netpbm.o
	gcc $(CFLAGS) main.c netpbm.o -o main -lm

netpbm.o:netpbm.h netpbm.c
	gcc $(CFLAGS) -c netpbm.c -lm
ppm:
	convert ./*.ppm ./*.jpg
clean:
	rm *.o main

cleanppm:
	rm *.ppm
