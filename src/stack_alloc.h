#include <ualloc.h>

int8_t stack_alloc_init(size_t size, stack_allocator * allocator){
    allocator->buffer = malloc(size);
    allocator->position = allocator->buffer;
    if (!allocator->buffer){
        allocator->size = 0;
        return 1;
    }
    allocator->size=0;
    return 0;
}
int8_t stack_alloc(size_t size, stack_allocator *allocator, void **buff_ptr){
    if (allocator->position + size + sizeof(size_t) > allocator->buffer + allocator->size){
        return 1;
    }
    *buff_ptr = allocator->position;
    allocator->position += size;
    *(void **) allocator->position = *buff_ptr;
    allocator->position += sizeof(void *);
}
void stack_free(stack_allocator * allocator){
    allocator->position = *(allocator->position - sizeof(void*));
}
void stack_destroy(stack_allocator * allocator){
    free(allocator->buffer);
    *allocator = {NULL,NULL,0};
} 
