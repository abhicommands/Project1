CFLAGS = -g -std=c99 -Wall -fsanitize=address,undefined
CC = gcc

all: err.o mymalloc.o 
	$(CC) $(CFLAGS) err.o mymalloc.o -o err
	mv err ./build
	rm -f *.o

err.o: err.c mymalloc.h
	$(CC) $(CFLAGS) -c err.c

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc.c