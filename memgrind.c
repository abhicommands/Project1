#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"

#define TEST_SIZE 120
#define TEST_REPEATS 50

void test1()
{
    int i, j;
    double total = 0;
    for (i = 0; i < TEST_REPEATS; i++)
    {
        clock_t start = clock();
        for (j = 0; j < TEST_SIZE; j++)
        {
            char *ptr = (char *)malloc(1);
            free(ptr);
        }
        clock_t end = clock();
        double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        total += elapsed;
    }
    printf("Average test 1 runtime after 50 repeats : %f seconds\n", total/TEST_REPEATS);
}

void test2()
{
    int i, j;
    double total = 0;
    for (i = 0; i < TEST_REPEATS; i++)
    {
        clock_t start = clock();
        char *ptrs[TEST_SIZE];
        for (j = 0; j < TEST_SIZE; j++)
        {
            ptrs[j] = (char *)malloc(1);
        }
        for (j = 0; j < TEST_SIZE; j++)
        {
            free(ptrs[j]);
        }
        clock_t end = clock();
        double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        total += elapsed;
    }
    printf("Average test 2 runtime after 50 repeats : %f seconds\n", total/TEST_REPEATS);
}

void test3()
{
    int i, j;
    double total = 0;
    for (i = 0; i < TEST_REPEATS; i++)
    {
        clock_t start = clock();
        char *ptrs[TEST_SIZE];
        int num_ptrs = 0;
        for (j = 0; j < TEST_SIZE; j++)
        {
            int action = rand() % 2;
            if (action == 0 && num_ptrs < TEST_SIZE)
            {
                ptrs[num_ptrs] = (char *)malloc(1);
                num_ptrs++;
            }
            else if (num_ptrs > 0)
            {
                int index = rand() % num_ptrs;
                free(ptrs[index]);
                ptrs[index] = ptrs[num_ptrs - 1];
                num_ptrs--;
            }
        }
        for (j = 0; j < num_ptrs; j++)
        {
            free(ptrs[j]);
        }
        clock_t end = clock();
        double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        total += elapsed;
    }
    printf("Average test 3 runtime after 50 repeats : %f seconds\n", total/TEST_REPEATS);
}

int main()
{
    srand(time(NULL));
    test1();
    test2();
    test3();
    return 0;
}
