#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include "ualloc.h"

new_test(heap_alloc_returns_1_on_failure){
    void * ptr;
    if(heap_alloc((size_t)~0, &ptr)){
        return 0;
    }
    puts("heap_alloc returned 0 on an invalid call.");
    return 1;
}

new_test(heap_free_sets_buffer_to_NULL){
    int a =2;
    void * ptr = &a ;
    heap_alloc(sizeof(int), &ptr);
    heap_free(&ptr);
    if(ptr){
        puts("Ptr not NULL after heap_free call");
        return 1;
    }
    return 0;
}

new_test(heap_alloc_sets_ptr){
    void * p = NULL;
    heap_alloc(sizeof(int), &p);
    if(p==NULL){
        puts("Pointer NULL after valid Malloc call");
        return 1;
    }
    heap_free(&p);
    return 0;
}


