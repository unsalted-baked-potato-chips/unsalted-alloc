#include <stdint.h>
#include "ualloc.h"

#define ALLOCATOR_SIZE 0x800

new_test(stack_alloc_initializes){
	stack_allocator allocator;
   return stack_alloc_init(ALLOCATOR_SIZE, &allocator);
}
new_test(stack_alloc_sets_size){

	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	return(allocator.size != ALLOCATOR_SIZE);
}
new_test(stack_alloc_offset_defaults_to_base_of_buffer){

	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	return (allocator.position != allocator.buffer);
}
new_test(stack_alloc_updates_buffer_address){
	stack_allocator allocator = {
		.size =0,
		.buffer = NULL,
		.position = NULL
	};

   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	return (allocator.buffer == NULL);
}
