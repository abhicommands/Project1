CFLAGS = -g -std=c99 -Wall -fsanitize=address,undefined
CC = gcc

performance: memgrind.o mymalloc.o 
	$(CC) $(CFLAGS) memgrind.o mymalloc.o -o memgrind
	mv memgrind ./build
	rm -f *.o

correctness: correctness.o mymalloc.o 
	$(CC) $(CFLAGS) correctness.o mymalloc.o -o correctness
	mv correctness ./build
	rm -f *.o

errcheck: err.o mymalloc.o 
	$(CC) $(CFLAGS) err.o mymalloc.o -o err
	mv err ./build
	rm -f *.o

err.o: err.c mymalloc.h
	$(CC) $(CFLAGS) -c err.c

memgrind.o: memgrind.c mymalloc.h
	$(CC) $(CFLAGS) -c memgrind.c

correctness.o: correctness.c mymalloc.h
	$(CC) $(CFLAGS) -c correctness.c

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc.c