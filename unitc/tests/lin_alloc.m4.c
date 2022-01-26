#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include "ualloc.h"

#define LIN_ALLOC_LEN sizeof(uint8_t)*0x800

new_test(lin_alloc_init_test){
    linear_allocator lin;
    const int res = lin_alloc_init(LIN_ALLOC_LEN, &lin);
    if (res){
        printf("lin_alloc_init failed. Return status: %d\n", res);
        return 1;
    }
    if (lin.size != LIN_ALLOC_LEN){
        printf("Linear Allocator size mismatch. Expected %lu. Got %lu\n", LIN_ALLOC_LEN, lin.size);
        return 1;
    }
    if (lin.buffer==NULL){
        puts("Linear Allocator buffer is NULL");
        return 1;
    }
    if (lin.position==NULL){
        puts("Linear Allocator position is NULL");
        return 1;
    }
    if (lin.position != lin.buffer){
        printf("Linear Allocator position is not initializes to start of buffer. Expected %p. Got %p.\n", lin.buffer, lin.position);
        return 1;
    }
    lin_destroy(&lin); 
    return 0;
}
new_test(lin_alloc_init_returns_MALLOC_FAILED_on_invalid_allocation_size){
    linear_allocator lin;
    return !(lin_alloc_init(~0, &lin)==UALLOC_MALLOC_FAILED);
}
new_test(lin_destroy_deletes_data_in_allocator_struct){
    linear_allocator lin;
    const size_t alloc_len = 64;
    lin_alloc_init(alloc_len, &lin);
    
    lin_destroy(&lin);
    if (lin.buffer){
        puts("Linear Allocator buffer member is not NULL after freeing.");
        return 1;
    }
    if (lin.position){
        puts("Linear Allocator position member is not NULL after freeing.");
        return 1;
    }
    if (lin.size){
        puts("Linear Allocator size member is not 0 after freeing.");
        return 1;
    }
    return 0;
}

new_test(lin_alloc_offset_test){
    linear_allocator lin;
    const size_t alloc_len = 64;
    lin_alloc_init(LIN_ALLOC_LEN, &lin);
    void * alloc_buffer;
    lin_alloc(alloc_len, &lin, &alloc_buffer);
    if ((uint8_t *)lin.position != ((uint8_t *)lin.buffer + alloc_len)){
        printf("Linear Allocator offset position mismatch. Expected %p, Got %p.\n", lin.position, (uint8_t *)lin.buffer + alloc_len);
        return 1;
    }
    lin_destroy(&lin);
    return 0;
}
new_test(lin_alloc_overflow_prevented){
    linear_allocator lin;
    const size_t alloc_len = LIN_ALLOC_LEN+1;
    lin_alloc_init(LIN_ALLOC_LEN, &lin);
    void * alloc_buffer;
    if (lin_alloc(alloc_len, &lin, &alloc_buffer)){
        return 0;
    }
    puts("Linear Allocator Overflown");
    lin_destroy(&lin);
    return 1;

}

new_test(lin_alloc_returns_UALLOC_ALLOCATOR_INSUFFICIENT_SPACE_on_potential_overflow){
    linear_allocator lin;
    const size_t alloc_len = LIN_ALLOC_LEN+1;
    lin_alloc_init(LIN_ALLOC_LEN, &lin);
    void * alloc_buffer;
    return !(lin_alloc(alloc_len, &lin, &alloc_buffer) == UALLOC_ALLOCATOR_INSUFFICIENT_SPACE);

}
new_test(lin_alloc_free_all_test){
    linear_allocator lin;
    const size_t alloc_len = 64;
    lin_alloc_init(LIN_ALLOC_LEN, &lin);
    void * alloc_buffer;
    lin_alloc(alloc_len, &lin, &alloc_buffer);
    lin_alloc(alloc_len, &lin, &alloc_buffer);
    lin_alloc(alloc_len, &lin, &alloc_buffer);
    lin_free_all(&lin);
    if (lin.position != lin.buffer){
        printf("Linear Allocator failed to free memory. Position: %p, Buffer %p\n", lin.position,lin.buffer);
        return 1;
    }
    lin_destroy(&lin);
    return 0;

}

new_test(lin_alloc_offset_after_two_allocations_test){
    linear_allocator lin;
    const size_t alloc_len = 64;
    lin_alloc_init(LIN_ALLOC_LEN, &lin);
    void * alloc_buffer;
    lin_alloc(alloc_len, &lin, &alloc_buffer);
    if ((uint8_t *)lin.position != ((uint8_t *)lin.buffer + alloc_len)){
        printf("Linear Allocator offset position mismatch after first allocation. Expected %p, Got %p.\n", lin.position, (uint8_t *)lin.buffer + alloc_len);
        return 1;
    }
    if ((uint8_t *)lin.position != ((uint8_t *)lin.buffer + alloc_len)){
        printf("Linear Allocator offset position mismatch after second allocation. Expected %p, Got %p.\n", lin.position, (uint8_t *)lin.buffer + alloc_len);
        return 1;
    }
    
    lin_destroy(&lin);
    return 0;
}
