# Abhinav Acharya 
NetID: aa2372
# Akshith Dandemraju
NetID: acd218

# Implimentation:
Our implementation requires that a block contain 4 bytes of data for integer stating if its a true or a false, 1 = free, and 0 is not free. The next 8 bytes stores a unsigned size_t that stores the size of the payload. The next 12 bytes will store the data of the next header. This means that any header will have 24 bytes of just data regarding the chunk header and the rest will be aligned properly with 8 bytes but contain the payload. This means in the performance testing for test 2, we can store 128 test size, if we go higher than 128 test size it should show that the memory can't handle that much extra memory and return the data to the user. Hence 128 is the max for our implementation. 
# Error Handling:
This library detects the following errors-<br />
    -Calling free() on a pointer that was not obtained by malloc().<br />
        This error will return "Error: Attempted to free invalid pointer at File Line" <br />
    -Calling free() with an address not at the start of a chunk.<br />
        This error will return "Error: Attempted to free invalid pointer at  File Line" <br />
    -Calling free() a second time on the same pointer.<br />
        This error will return "Error: Attempted to free already freed pointer at File Line" <br />
    -Calling Malloc with invalid size <br />
        This error will return "Error: Invalid allocation size at File Line" <br />
        In addition we cannot check if the size is less than 0 because size_t is a unsigned unit <br />
    -Calling Malloc with an object that doesn't have anymore space in the array. <br />
        This error will return "Error: Out of memory at File Line" <br />
# Correctness Testing:
To ensure that all the programs run correctly here are the tests we are running-<br />
    -malloc() reserves unallocated memory.<br />
        To test this case we call malloc on a pointer and check if the pointer is null. If malloc was successful the pointer will not be null. <br/>
    -When successful, malloc() returns a pointer to an object that does not overlap with any other allocated object.<br />
        To test this case we malloc 3 pointers and verify if the length that they are allocated to is the correct address. <br/>
    -A program that allocates several large objects. Once allocation is complete, it fills each object with a distinct byte pattern (e.g., the first object is filled with 1, the second with 2 etc.). Finally, it checks whether each object still contains the written pattern. (That is, writing to one object did not overwrite any other.) <br/>
    To test this we just create 3 arrays with malloc and go through them to check that they have the right information in them. This shows that even after they all were malloced they did not overwrite any information.<br />
    -free() deallocates memory <br />
    To test this we malloced 3 pointers and freed the middle pointer and then malloced another pointer with the same size as the freed one. And If the new pointer did not go into the place of the freed pointer we would know that it is wrong. <br/>
    -malloc() and free() arrange so that adjacent free blocks are coalesced<br />
    To test this we malloced 2 pointers with the total size of 150 and then malloced another pointer after them. We then freed the first two pointers which means that if the array was coalesed then the first chunck should be freed and the size of 150. Then we malloced a 150 size pointer which should be in the same address as the first pointer since it would go in to the beginning. <br/>

# Performance Testing:
In the memgrind file we test the performance and the runtimes of the library. Here are the following tests-<br />
    -malloc() and immediately free() a 1-byte chunk, 120 times.<br />
    -Use malloc() to get 120 1-byte chunks, storing the pointers in an array, then use free() to deallocate the chunks<br />
    -Randomly choose between:<br />
        •Allocating a 1-byte chunk and storing the pointer in an array<br />
        •Deallocating one of the chunks in the array (if any)<br />
    Repeat until you have called malloc() 120 times, then free all remaining allocated chunks.<br />
    - in the 4 test we decided to test the coalescing and how good it is, so we tried to performance test and brute force the time for coalescing. <br/>
    - in test 5, we first allocate half the test size then we free half, then we again allocate half the test size and then free the rest. This way we can test if the program is not biased in the order we free and malloc. 
<br />
Each of these tests are run 50 times in order to find the average performance.
