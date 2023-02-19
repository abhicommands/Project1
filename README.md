# Abhinav Acharya 
NetID: aa2372
# Akshith Dandemraju
NetID: acd218

# Error Handling:
This library detects the following errors-<br />
    -Calling free() on a pointer that was not obtained by malloc().<br />
        //Explain the error handling and reporting<br />
    -Calling free() with an address not at the start of a chunk.<br />
        //Explain the error handling and reporting<br />
    -Calling free() a second time on the same pointer.<br />
        //Explain the error handling and reporting<br />
# Correctness Testing:
To ensure that all the programs run correctly here are the tests we are running-<br />
    -malloc() reserves unallocated memory.<br />
    -When successful, malloc() returns a pointer to an object that does not overlap with any other allocated object.<br />
    -A program that allocates several large objects. Once allocation is complete, it fills each object with a distinct byte pattern (e.g., the first object is filled with 1, the second with 2 etc.). Finally, it checks whether each object still contains the written pattern. (That is, writing to one object did not overwrite any other.)<br />
    -free() deallocates memory<br />
    -malloc() and free() arrange so that adjacent free blocks are coalesced<br />

# Performance Testing:
In the memgrind file we test the performance and the runtimes of the library. Here are the following tests-<br />
    -malloc() and immediately free() a 1-byte chunk, 120 times.<br />
    -Use malloc() to get 120 1-byte chunks, storing the pointers in an array, then use free() to deallocate the chunks<br />
    -Randomly choose between:<br />
        •Allocating a 1-byte chunk and storing the pointer in an array<br />
        •Deallocating one of the chunks in the array (if any)<br />
    Repeat until you have called malloc() 120 times, then free all remaining allocated chunks.<br />
    -two more stress tests of your design<br />
<br />
Each of these tests are run 50 times in order to find the average performance.
