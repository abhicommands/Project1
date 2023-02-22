#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 4096

typedef struct block {
    size_t size;
    int free;
    struct block *next;
} Block;

static char memory[MEMORY_SIZE];
static Block *head = (Block*) memory;
static int initialized = 0;

void initialize() {
    head->size = MEMORY_SIZE - sizeof(Block);
    head->free = 1;
    head->next = NULL;
    initialized = 1;
}

void split(Block *fitting_slot, size_t size) {
    Block *new = (void*)((void*)fitting_slot + size + sizeof(Block));
    new->size = (fitting_slot->size) - size - sizeof(Block);
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

    if (size <= 0) {
        fprintf(stderr, "Error: Invalid allocation size at %s:%d\n", file, line);
        return NULL;
    }

    Block *curr = head;
    while (curr != NULL) {
        if (curr->free && curr->size >= size) {
            if (curr->size >= size + sizeof(Block) + 1) {
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

    Block *curr = (Block*)memory;
    Block *prev = NULL;
    while (curr != NULL && curr != (Block*)ptr - 1) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        fprintf(stderr, "Error: Attempted to free invalid pointer at %s:%d\n", file, line);
        return;
    }

    if (curr->free) {
        fprintf(stderr, "Error: Attempted to free already freed pointer at %s:%d\n", file, line);
        return;
    }

    curr->free = 1;

    if (prev != NULL && prev->free) {
        prev->size += sizeof(Block) + curr->size;
        prev->next = curr->next;
        curr = prev;
    }

    if (curr->next != NULL && curr->next->free) {
        curr->size += sizeof(Block) + curr->next->size;
        curr->next = curr->next->next;
    }
}
