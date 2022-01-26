#include <stdint.h>
#include <stdlib.h>
#include "ualloc.h"

typedef uint8_t byte;

int8_t stack_alloc_init(size_t size, stack_allocator *allocator){
	allocator->size = size;
	allocator->buffer = malloc (size);
	if (allocator->buffer == NULL){
		return 1;
	}
	allocator->position = allocator->buffer;
	return 0;
}
int8_t stack_alloc(size_t size, stack_allocator *allocator, void ** allocation){
	byte * pos = allocator->position;
	byte * buff = allocator->buffer;

	if(pos+size > buff + allocator->size){
		return 1;
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
		return 1;
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
