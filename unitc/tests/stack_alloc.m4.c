#include <stdint.h>
#include <string.h>
#include "ualloc.h"

#define ALLOCATOR_SIZE 0x800

typedef uint8_t byte;

new_test(stack_alloc_initializes){
	stack_allocator allocator;
   return stack_alloc_init(ALLOCATOR_SIZE, &allocator);
}
new_test(stack_alloc_init_returns_MALLOC_FAILED_with_invalid_size){
	stack_allocator allocator;
   return !(stack_alloc_init(~0, &allocator) == UALLOC_MALLOC_FAILED);
}
new_test(stack_alloc_sets_size){

	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	return !(allocator.size == ALLOCATOR_SIZE);
}
new_test(stack_alloc_init_fails_on_invalid_size){
	stack_allocator allocator;
	return !(stack_alloc_init(~0, &allocator));
}
new_test(stack_alloc_offset_defaults_to_base_of_buffer){

	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	return !(allocator.position == allocator.buffer);
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
	return !(allocator.buffer != NULL);
}
new_test(stack_alloc_allocate_new_block){

	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	int *a = NULL;
	uint8_t alloc = stack_alloc(sizeof(int), & allocator, (void **)&a);
	return alloc;
}
new_test(stack_alloc_new_block_not_null){

	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	int *a = NULL;
	uint8_t alloc = stack_alloc(sizeof(int), & allocator, (void **)&a);
	if(alloc){
		puts("Failed to allocate memory in stack allocator");
		return 1;
	}
	return !(a!=NULL);
}

new_test(stack_alloc_position_pointer_moves_after_new_allocation){

	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	int *a = NULL;
	uint8_t alloc = stack_alloc(sizeof(int), & allocator, (void **)&a);
	if(alloc){
		puts("Failed to allocate memory in stack allocator");
		return 1;
	}
	byte * pos = allocator.position;
	byte * buff = allocator.buffer;
	return !(pos == buff + sizeof(int) + sizeof(void *));
}

new_test(stack_alloc_footer_inserted_after_first_allocation){

	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	int *a = NULL;
	uint8_t alloc = stack_alloc(sizeof(int), & allocator, (void **)&a);
	if(alloc){
		puts("Failed to allocate memory in stack allocator");
		return 1;
	}
	byte * pos = allocator.position;
	void **footer =(void **) (pos - sizeof(void *));
	return !(*footer == allocator.buffer);
}

new_test(stack_alloc_allocate_two_block_neither_null_nor_equivalent){

	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	int *a = NULL;
	int *b = NULL;
	uint8_t alloc = stack_alloc(sizeof(int), & allocator, (void **)&a);
	if(alloc){
		puts("Failed to allocate memory in stack allocator");
		return 1;
	}
	alloc = stack_alloc(sizeof(int), & allocator, (void **)&b);
	if(alloc){
		puts("Failed to allocate memory in stack allocator");
		return 1;
	}

	return !(b!=a && a!=NULL &&b!=NULL);
}

new_test(stack_alloc_footer_points_to_end_first_block_after_second_allocation){

	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	int *a = NULL;
	int *b = NULL;
	uint8_t alloc = stack_alloc(sizeof(int), & allocator, (void **)&a);
	if(alloc){
		puts("Failed to allocate memory in stack allocator");
		return 1;
	}
	void * end_of_block_one = allocator.position;
	alloc = stack_alloc(sizeof(int), & allocator, (void **)&b);
	if(alloc){
		puts("Failed to allocate memory in stack allocator");
		return 1;
	}

	byte * pos = allocator.position;
	void **footer =(void **) (pos - sizeof(void *));
	return !(*footer == end_of_block_one);
}
new_test(stack_alloc_prevent_overflow){
	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	int *a = NULL;
	uint8_t alloc = stack_alloc(ALLOCATOR_SIZE+1, & allocator, (void **)&a);
	return !(alloc);
}

new_test(stack_alloc_returns_ALLOCATOR_INSUFFICIENT_SPACE_on_potential_overflow){
	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	int *a = NULL;
	uint8_t alloc = stack_alloc(ALLOCATOR_SIZE+1, & allocator, (void **)&a);
	return !(alloc==UALLOC_ALLOCATOR_INSUFFICIENT_SPACE);
}

new_test(stack_free_resets_position_to_buffer_head_after_one_allocation){

	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	int *a = NULL;
	uint8_t alloc = stack_alloc(sizeof(int), & allocator, (void **)&a);
	if(alloc){
		puts("Failed to allocate memory in stack allocator");
		return 1;
	}
	stack_free(&allocator);
	return !(allocator.position == allocator.buffer);
}

new_test(stack_free_resets_position_to_end_of_block_one_foot_after_two_allocations){

	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}

	int *a = NULL;
	int *b = NULL;
	uint8_t alloc = stack_alloc(sizeof(int), & allocator, (void **)&a);
	if(alloc){
		puts("Failed to allocate memory in stack allocator");
		return 1;
	}
	void * end_of_block_one = allocator.position;
	alloc = stack_alloc(sizeof(int), & allocator, (void **)&b);
	if(alloc){
		puts("Failed to allocate memory in stack allocator");
		return 1;
	}

	stack_free(&allocator);
	return !(allocator.position == end_of_block_one);
}
new_test(stack_free_fails_on_empty_stack){

	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	return !(stack_free(&allocator));
}
new_test(stack_free_returns_STACK_EMPTY_on_empty_stack){

	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	return !(stack_free(&allocator)==UALLOC_STACK_EMPTY);
}

new_test(stack_destroy_sets_allocator_member_pointers_to_null){

	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	stack_destroy(&allocator);
	return !(allocator.buffer ==NULL && allocator.position==NULL);
}

new_test(stack_alloc_passes_memcmp){

	stack_allocator allocator;
   int8_t init = stack_alloc_init(ALLOCATOR_SIZE, &allocator);
	if(init){
		puts("Failed to init stack allocator");
		return 1;
	}
	byte * buff = allocator.buffer;
	void *data[6] = {(void*)1, (void*)2, (void*)3, (void*)4, (void*)5, (void*)6};
	data[1] = buff;
	data[3] = buff +2*sizeof(void *);
	data[5] = buff +4*sizeof(void *);
	void **a = NULL;
	stack_alloc(sizeof(void*), &allocator, (void **)&a);
	*a = data[0];
	stack_alloc(sizeof(void*), &allocator, (void **)&a);
	*a = data[2];
	stack_alloc(sizeof(void*), &allocator, (void **)&a);
	*a = data[4];

	if (memcmp(data, allocator.buffer, 6*sizeof(void *))==0){
		return 0;
	}
	puts("Expected:");
	byte * data_b = (byte *) data;
	for (int i = 0; i<6*sizeof(void *); i++){
		if (i%8 ==0 && i>0){
			putchar(' ');
		}
		printf("%02X", data_b[i]);
	}
	puts("\nGot:");
	for (int i = 0; i<6*sizeof(void *); i++){
		if (i%8 ==0 && i>0){
			putchar(' ');
		}
		printf("%02X", buff[i]);
	}
	putchar('\n');
	return 1; 
}

