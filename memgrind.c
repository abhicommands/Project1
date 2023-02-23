#include <stdio.h>
#include <string.h>
#include "mymalloc.h"

int main() {
    // Test case 1: malloc() reserves unallocated memory
    int *ptr1 = (int*) malloc(100);
    int *ptr2 = (int*) malloc(100);
    int *ptr3 = (int*) malloc(100);
    printf("ptr2: %p ", ptr2);
    printf("\n");
    printList();
    free(ptr2);
    printList();
    int *ptr4 = (int*) malloc(100);
    printf("ptr4: %p ", ptr4);
    printf("\n");
    printList();
    return 0;
}