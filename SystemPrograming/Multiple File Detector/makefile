CFLAGS= -pedantic -Wall -g -ansi
CC = gcc

doall: finddup.o hash.o md5m.o init.o filecheck

filecheck : finddup.o hash.o md5m.o init.o
	$(CC) -o filecheck finddup.o hash.o md5m.o init.o -lcrypto -lssl

finddup.o : finddup.c finddup.h md5m.h init.h hash.h
	$(CC)  -c $(CFLAGS) finddup.c -lstat

init.o : init.c init.h hash.h
	$(CC)  -c $(CFLAGS) init.c

md5m.o : md5m.c md5m.h
	$(CC) -c $(CFLAGS) md5m.c -lcrypto -lssl

hash.o : hash.c hash.h
	$(CC)  -c $(CFLAGS) hash.c
clean:
	rm -f *.o
	rm prog
