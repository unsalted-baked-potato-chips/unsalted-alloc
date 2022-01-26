#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include "ualloc.h"

int8_t lin_alloc_init(size_t size, linear_allocator * allocator){
    allocator->buffer = malloc(size);
    if (!allocator->buffer){
        *allocator = (linear_allocator) {NULL, NULL, 0};
        return UALLOC_MALLOC_FAILED;
    }
    allocator->position = allocator->buffer;
    allocator->size = size;
    return 0;
}

int8_t lin_alloc(size_t size, linear_allocator * allocator, void ** buffer){
    uint8_t * pos = (uint8_t *)allocator->position;
    uint8_t * buff = (uint8_t *)allocator->buffer;
    if (pos + size > (buff+allocator->size)){
        return UALLOC_ALLOCATOR_INSUFFICIENT_SPACE;
    }
    allocator->position = (void *)(pos + size);
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
