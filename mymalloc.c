#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define MEMORY_SIZE 4096

typedef struct chunk {
    size_t size;
    int free;
    struct chunk *next;
} Chunk;

static char memory[MEMORY_SIZE];
static Chunk *head = (Chunk*) memory;
static int initialized = 0;

void initialize() {
    head->size = MEMORY_SIZE - sizeof(Chunk);
    head->free = 1;
    head->next = NULL;
    initialized = 1;
}

void split(Chunk *fitting_slot, size_t size) {
    Chunk *new = (void*)((void*)fitting_slot + size + sizeof(Chunk));
    new->size = (fitting_slot->size) - size - sizeof(Chunk);
    new->free = 1;
    new->next = fitting_slot->next;
    fitting_slot->size = size;
    fitting_slot->free = 0;
    fitting_slot->next = new;
}

void *mymalloc(size_t size, char* file, int line) {
    if (!initialized) {
        initialize();
    }

    if (size == 0) {
        fprintf(stderr, "Error: Invalid allocation size at %s:%d\n", file, line);
        return NULL;
    }
    size = size + sizeof(Chunk);
    if (size % 8 != 0) {
        size = size + (8 - size % 8);
        size = size - sizeof(Chunk);
    }
    Chunk *curr = head;
    while (curr != NULL) {
        if (curr->free && curr->size >= size) {
            if (curr->size >= size + sizeof(Chunk)+1) {
                split(curr, size);
            }
            curr->free = 0;
            return (void*)(curr + 1);
        }
        curr = curr->next;
    }

    fprintf(stderr, "Error: Out of memory at %s:%d\n", file, line);
    return NULL;
}

void myfree(void* ptr, char* file, int line) {
    if (!initialized) {
        initialize();
    }

    if (ptr == NULL) {
        fprintf(stderr, "Error: Attempted to free null pointer at %s:%d\n", file, line);
        return;
    }

    Chunk *curr = (Chunk*)memory;
    Chunk *prev = NULL;
    while (curr != NULL && curr != (Chunk*)ptr - 1) {
        prev = curr;
        curr = curr->next;
    }
    if(curr == NULL) {
        fprintf(stderr, "Error: Attempted to free invalid pointer at %s:%d\n", file, line);
        return;
    }
    if(curr + 1 != ptr) {
        fprintf(stderr, "Error: Attempted to free non-starting pointer at %s:%d\n", file, line);
        return;
    }
    if (curr->free) {
        fprintf(stderr, "Error: Attempted to free already freed pointer at %s:%d\n", file, line);
        return;
    }

    curr->free = 1;

    if (prev != NULL && prev->free) {
        prev->size += sizeof(Chunk) + curr->size;
        prev->next = curr->next;
        curr = prev;
    }

    if (curr->next != NULL && curr->next->free) {
        curr->size += sizeof(Chunk) + curr->next->size;
        curr->next = curr->next->next;
    }
}
/*

void printList() {
    Chunk *curr = head;
    while (curr != NULL) {
        printf("Chunk at %p, size %d, free %d, next %p", curr, curr->size, curr->free, curr->next);
        printf("\n");
        curr = curr->next;
    }
}
This is the output of the entire mempory allocation process: which is important because we used this to debug our code.
*/