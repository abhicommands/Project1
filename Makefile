CFLAGS = -g -std=c99 -Wall -fsanitize=address,undefined
CC = gcc

correctness: memgrind.o mymalloc.o 
	$(CC) $(CFLAGS) memgrind.o mymalloc.o -o memgrind
	mv memgrind ./build
	rm -f *.o

correctnessabhi: memgrindabhi.o mymalloc.o 
	$(CC) $(CFLAGS) memgrindabhi.o mymalloc.o -o memgrindabhi
	mv memgrindabhi ./build
	rm -f *.o

errcheck: err.o mymalloc.o 
	$(CC) $(CFLAGS) err.o mymalloc.o -o err
	mv err ./build
	rm -f *.o

err.o: err.c mymalloc.h
	$(CC) $(CFLAGS) -c err.c

memgrind.o: memgrind.c mymalloc.h
	$(CC) $(CFLAGS) -c memgrind.c

memgrindabhi.o: memgrindabhi.c mymalloc.h
	$(CC) $(CFLAGS) -c memgrindabhi.c

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc.c