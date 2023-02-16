#include <stdio.h>
#include <stdbool.h>
#include "mymalloc.h"

static char memory[4096]; 
static char *next_allocation = 0;

typedef struct chuck_header{
    bool isFree;
    size_t size;
}chunk_header;

void *mymalloc(size_t size) {
    // size of the chuck must include header
    size += sizeof(chunk_header);
    
    if (next_allocation + size > sizeof(memory)) {
        return NULL;  // No space
    }
    
    // Header creation
    chunk_header *header = (chunk_header*)(next_allocation);
    header->size = size;
    header->isFree = true;
    
    // Update next_allocation 
    next_allocation += size;
    
    // Return pointer to user portion of chunk
    return (void*)(header + 1);
}

void myfree(void *ptr) {
    if (ptr == NULL) {
        return;  // Do nothing if null pointer
    }
    
    // Get header of chunk to be freed
    chunk_header* header = ((chunk_header*)ptr) - 1;
    header->isFree = false;
    
    // Check if adjacent chunks are free and coalesce if necessary
    chunk_header* next_header = (chunk_header*)((char*)header + header->size);
    if (next_header < (chunk_header*)(memory + sizeof(memory)) && !next_header->isFree) {
        header->size += next_header->size;
    }
    chunk_header* prev_header = (chunk_header*)((char*)header - sizeof(chunk_header));
    if (prev_header >= (chunk_header*)memory && !prev_header->isFree) {
        prev_header->size += header->size;
        prev_header->isFree = false;
    }
}