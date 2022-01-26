#include <stdint.h>
#include <stdlib.h>
#include "ualloc.h"

typedef uint8_t byte;

int8_t stack_alloc_init(size_t size, stack_allocator *allocator){
	allocator->size = size;
	allocator->buffer = malloc (size);
	allocator->position = allocator->buffer;
	return (allocator->buffer == NULL) & UALLOC_MALLOC_FAILED;
}
int8_t stack_alloc(size_t size, stack_allocator *allocator, void ** allocation){
	byte * pos = allocator->position;
	byte * buff = allocator->buffer;

	if(pos+size > buff + allocator->size){
		return UALLOC_ALLOCATOR_INSUFFICIENT_SPACE;
	}

	pos = pos + size + sizeof(void *);
	*allocation = allocator->position;
	

	void **footer = (void **)(pos-sizeof(void*));
	*footer=allocator->position;

	allocator->position = pos;
	allocator->buffer = buff;
	return 0;
}
int8_t stack_free(stack_allocator *allocator){
	if (allocator->buffer == allocator->position){
		return UALLOC_STACK_EMPTY;
	}

	byte * pos = allocator->position;
	void **footer = (void **)(pos-sizeof(void*));
	allocator->position = *footer;
	return 0;
}
void stack_destroy(stack_allocator * allocator){
	free(allocator->buffer);
	allocator->buffer = NULL;
	allocator->position = NULL;
}
