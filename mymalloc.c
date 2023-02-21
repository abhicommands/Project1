#include <stdio.h>
#include <stdbool.h>
#include "mymalloc.h"

typedef struct chunkHeader{
    bool isFree;
    size_t size;
}chunk_header;

static char memory[4096]; 

static chunk_header* next_allocation = (chunk_header*)(memory);
next_allocation->isFree = true;
next_allocation->size = sizeof(memory);

void *mymalloc(size_t size) {
    // size of the chuck must include header
    size += sizeof(chunk_header);
    
    // Find free chunk of sufficient size
    chunk_header* header = next_allocation;
    while (header < (chunk_header*)sizeof(memory)) {
        if (header->isFree && header->size < size) {
            header->isFree = false;
            header->size = size;
            next_allocation = (chunk_header*)((char*)header + header->size);
            break;
        } else {
            header = (chunk_header*)((char*)header + header->size);
        }
    }
    
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