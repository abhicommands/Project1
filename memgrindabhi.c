#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymalloc.h"

#define TEST_SIZE 10000

void test1() {
    // Test that malloc reserves unallocated memory
    char* ptr = (char*) malloc(100);
    if (ptr == NULL) {
        printf("Test 1 failed: ptr is NULL\n");
        return;
    }
    free(ptr);
    printf("Test 1 passed\n");
}

void test2() {
    // Test that malloc returns a pointer to an object that does not overlap with any other allocated object
    char* ptr1 = (char*) malloc(50);
    char* ptr2 = (char*) malloc(100);
    char* ptr3 = (char*) malloc(150);
    if ((ptr1 + 50) == ptr2 || (ptr2 + 100) == ptr3) {
        printf("Test 2 failed: pointers overlap\n");
        return;
    }
    free(ptr1);
    free(ptr2);
    free(ptr3);
    printf("Test 2 passed\n");
}

void test3() {
    // Test that writing to one object did not overwrite any other
    int* ptr1 = (int*) malloc(TEST_SIZE * sizeof(int));
    int* ptr2 = (int*) malloc(TEST_SIZE * sizeof(int));
    int* ptr3 = (int*) malloc(TEST_SIZE * sizeof(int));
    for (int i = 0; i < TEST_SIZE; i++) {
        ptr1[i] = 1;
        ptr2[i] = 2;
        ptr3[i] = 3;
    }
    for (int i = 0; i < TEST_SIZE; i++) {
        if (ptr1[i] != 1 || ptr2[i] != 2 || ptr3[i] != 3) {
            printf("Test 3 failed: pattern overwritten\n");
            free(ptr1);
            free(ptr2);
            free(ptr3);
            return;
        }
    }
    free(ptr1);
    free(ptr2);
    free(ptr3);
    printf("Test 3 passed\n");
}

void test4() {
    // Test that free deallocates memory
    char* ptr = (char*) malloc(100);
    free(ptr);
    if (malloc_usable_size(ptr) != 0) {
        printf("Test 4 failed: ptr is still allocated\n");
        return;
    }
    printf("Test 4 passed\n");
}

void test5() {
    // Test that adjacent free blocks are coalesced
    char* ptr1 = (char*) malloc(100);
    char* ptr2 = (char*) malloc(50);
    free(ptr1);
    free(ptr2);
    char* ptr3 = (char*) malloc(150);
    if (ptr3 != ptr1) {
        printf("Test 5 failed: blocks not coalesced\n");
        return;
    }
    free(ptr3);
    printf("Test 5 passed\n");
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}
