CFLAGS= -pedantic -Wall -g -ansi
CC = gcc

hashcheck : hashtest.o hash.o
	$(CC) -o hashcheck hashtest.o hash.o

hashtest.o : hashtest.c hash.h
	$(CC)  -c $(CFLAGS)  hashtest.c

hash.o : hash.c hash.h
	$(CC)  -c $(CFLAGS)  hash.c

clean:
	rm -f *.o
	rm hashcheck