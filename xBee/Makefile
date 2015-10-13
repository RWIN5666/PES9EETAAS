CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -std=c99
LDFLAGS=
EXEC=comXbee

all: $(EXEC)

comXbee: comXbee.o
	$(CC) -o comXbee comXbee.o $(LDFLAGS)



comXbee.o: comXbee.c 
	$(CC) -o comXbee.o -c comXbee.c $(CFLAGS)

clean:
	rm -rf *.o
