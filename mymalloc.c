#include <stdio.h>
#include "mymalloc.h"

void *mymalloc(size_t size) {
    return size;
}
void myfree(void *ptr) {
    return ptr;
}