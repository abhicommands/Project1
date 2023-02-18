# Abhinav Acharya 
NetID: aa2372
# Akshith Dandemraju
NetID: acd218

# Error Handling:
This library detects the following errors-
    -Calling free() on a pointer that was not obtained by malloc().
        //Explain the error handling and reporting
    -Calling free() with an address not at the start of a chunk.
        //Explain the error handling and reporting
    -Calling free() a second time on the same pointer.
        //Explain the error handling and reporting
# Correctness Testing:
To ensure that all the programs run correctly here are the tests we are running-
    -malloc() reserves unallocated memory.
    -When successful, malloc() returns a pointer to an object that does not overlap with any other allocated object.
    -A program that allocates several large objects. Once allocation is complete, it fills each object with a distinct byte pattern (e.g., the first object is filled with 1, the second with 2 etc.). Finally, it checks whether each object still contains the written pattern. (That is, writing to one object did not overwrite any other.)
    -free() deallocates memory
    -malloc() and free() arrange so that adjacent free blocks are coalesced

# Performance Testing:
In the memgrind file we test the performance and the runtimes of the library. Here are the following tests-
    -malloc() and immediately free() a 1-byte chunk, 120 times.
    -Use malloc() to get 120 1-byte chunks, storing the pointers in an array, then use free() to deallocate the chunks
    -Randomly choose between:
        •Allocating a 1-byte chunk and storing the pointer in an array
        •Deallocating one of the chunks in the array (if any)
    Repeat until you have called malloc() 120 times, then free all remaining allocated chunks.
    -two more stress tests of your design

Each of these tests are run 50 times in order to find the average performance.