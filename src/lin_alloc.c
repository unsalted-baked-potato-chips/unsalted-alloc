#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include "ualloc.h"

int8_t lin_alloc_init(size_t size, linear_allocator * allocator){
    allocator->buffer = malloc(size);
    if (!allocator->buffer){
        *allocator = (linear_allocator) {NULL, NULL, 0};
        return 1;
    }
    allocator->position = allocator->buffer;
    allocator->size = size;
    return 0;
}

int8_t lin_alloc(size_t size, linear_allocator * allocator, void ** buffer){
    if ((uint8_t *)(allocator->position) + size > ((uint8_t *)allocator->buffer)+allocator->size){
        return 1;
    }
    allocator->position = (void *)(((uint8_t *)(allocator->position)) + size);
    buffer = allocator->position;
    return 0;
}

void lin_free_all(linear_allocator * allocator){
    allocator->position = allocator->buffer;
}

void lin_destroy(linear_allocator * allocator){
    free(allocator->buffer);
    *allocator = (linear_allocator) {NULL,NULL,0};
}
