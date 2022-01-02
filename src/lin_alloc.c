#include "ualloc.h"

int8_t lin_alloc_init(size_t size, linear_allocator * allocator){
    allocator->buffer = malloc(size);
    if (!allocator->buffer){
        *allocator = {NULL, NULL, 0};
        return 1;
    }
    allocator->position = allocator->buffer;
    allocator->size = size;
}

int8_t lin_alloc(size_t size, linear_allocator * allocator, void ** buffer){
    if (allocator->position + size > allocator->buffer+allocator->size){
        return 1;
    }
    allocator->position += size;
    buffer = allocator->position;
}

void lin_clear(linear_allocator * allocator){
    allocator->position = allocator->buffer;
}

void lin_destroy(linear_allocator * allocator){
    free(allocator->buffer);
    *allocator = {NULL,NULL,0};
}
