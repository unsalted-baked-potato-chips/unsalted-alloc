#include <stdint.h>
#include <stdlib.h>
#include "ualloc.h"

int8_t stack_alloc_init(size_t size, stack_allocator *allocator){
	allocator->size = size;
	allocator->buffer = malloc (size);
	if (allocator->buffer == NULL){
		return 1;
	}
	allocator->position = allocator->buffer;
	return 0;
}
