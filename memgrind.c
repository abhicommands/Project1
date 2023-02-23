#include <stdio.h>
#include <string.h>
#include "mymalloc.h"

int main() {
    // Test case 1: malloc() reserves unallocated memory
    int *ptr1 = (int*) malloc(100);
    int *ptr2 = (int*) malloc(100);

    printf("ptr2: %p ", &ptr2);
    int *ptr3 = (int*) malloc(100);
    free(ptr2);
    int *ptr4 = (int*) malloc(100);
    printf("ptr4: %p ", &ptr4);


    // Test case 2: malloc() returns a pointer to an object that does not overlap with any other allocated object
    int *int_ptr = (int*) malloc(4);
    char *char_ptr = (char*) malloc(100);
    if (char_ptr <= (char*) int_ptr + 3) {
        printf("Test case 2 failed: allocated objects overlap\n");
    }

    // Test case 3: writing to one object does not overwrite any other
    char *str1 = (char*) malloc(1000);
    char *str2 = (char*) malloc(2000);
    memset(str1, '1', 1000);
    memset(str2, '2', 2000);
    for (int i = 0; i < 1000; i++) {
        if (str1[i] != '1') {
            printf("Test case 3 failed: object 1 has been overwritten\n");
            break;
        }
    }
    for (int i = 0; i < 2000; i++) {
        if (i < 1000 && str2[i] != '2') {
            printf("Test case 3 failed: object 2 has been overwritten before its start\n");
            break;
        } else if (i >= 1000 && str2[i] != '2') {
            printf("Test case 3 failed: object 2 has been overwritten after its end\n");
            break;
        }
    }

    // Test case 4: free() deallocates memory
    free(ptr1);
    if (ptr1!= NULL) {
        printf("Test case 4 failed: memory was not deallocated correctly\n");
    }

    // Test case 5: adjacent free blocks are coalesced
    free(ptr2);
    if (head->free == 0 || head->size != 300 + sizeof(Block)) {
        printf("Test case 5 failed: adjacent free blocks were not coalesced correctly\n");
    }

    return 0;
}
