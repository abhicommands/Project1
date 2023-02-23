#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymalloc.h"

#define TEST_SIZE 100

void test1() {
    char* ptr = (char*) malloc(100);
    if (ptr == NULL) {
        printf("Test 1 failed: ptr is NULL\n");
        return;
    }
    free(ptr);
    printf("Test 1 passed\n");
}

void test2() {
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
    int *ptr1 = (int*) malloc(100);
    int *ptr2 = (int*) malloc(100);
    int *ptr3 = (int*) malloc(100);
    free(ptr2);
    int *ptr4 = (int*) malloc(100);
    if (ptr4 != ptr2) {
        printf("Test 4 failed: ptr4 != ptr2\n");
        return;
    }
    free(ptr1);
    free(ptr3);
    free(ptr4);
    printf("Test 4 passed\n");
}

void test5() {
    char* ptr1 = (char*) malloc(100);
    char* ptr2 = (char*) malloc(50);
    char *ptr4 = (char*) malloc(100);
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
    // correctnesstests
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}
