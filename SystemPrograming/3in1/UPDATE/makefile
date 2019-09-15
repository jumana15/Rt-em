CFLAGS= -pedantic -g -ansi
CC = gcc

doall: finddup.o hash.o md5m.o init.o filecheck

filecheck : finddup.o hash.o md5m.o init.o wqueue.o
	$(CC) -o filecheck finddup.o hash.o md5m.o init.o wqueue.o -lcrypto -lssl -pthread -lrt 

finddup.o : finddup.c finddup.h md5m.h init.h hash.h wqueue.h
	$(CC)  -c $(CFLAGS) -lstat finddup.c

init.o : init.c init.h hash.h
	$(CC)  -c $(CFLAGS) init.c

md5m.o : md5m.c md5m.h
	$(CC) -c $(CFLAGS) -lcrypto -lssl md5m.c 

hash.o : hash.c hash.h
	$(CC)  -c $(CFLAGS) hash.c

wqueue.o : wqueue.c wqueue.h
	$(CC)  -c $(CFLAGS) -pthread -lrt wqueue.c

clean:
	rm -f *.o
	rm prog
