#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include "ualloc.h"

new_test(lin_alloc_init_test){
    const size_t len = sizeof(uint8_t)*0x800;
    linear_allocator lin;
    const int res = lin_alloc_init(len, &lin);
    if (res){
        printf("lin_alloc_init failed. Return status: %d\n", res);
        return 1;
    }
    if (lin.size != len){
        printf("Linear Allocator size mismatch. Expected %lu. Got %lu\n", len, lin.size);
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
    return 0;
}
