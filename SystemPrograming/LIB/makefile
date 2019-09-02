CFLAGS= -lN -L.
CC = gcc

prog : progA.o progB.o libN.so
	$(CC) -o prog progA.o progB.o $(CFLAGS)

progB.o : progB.c
	$(CC) -c progB.c

progA.o : progA.c
	$(CC) -c progA.c

libN.so : lib1.o lib2.o lib3.o
	$(CC) -o libN.so -shared lib1.o lib2.o lib3.o

lib3.o : lib3.c
	$(CC) -c -fPIC lib3.c

lib2.o : lib2.c
	$(CC) -c -fPIC lib2.c

lib1.o : lib1.c
	$(CC) -c -fPIC lib1.c

clean:
	rm -f *.o
	rm prog
