#include <stdio.h>
#include "mymalloc.h"

static char memory[4096]; 


void *mymalloc(size_t size) {
    return size;
}
void myfree(void *ptr) {
    return ptr;
}