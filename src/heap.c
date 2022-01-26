#include <stdlib.h>
#include <stddef.h>

#include "ualloc.h"

int heap_alloc(size_t size, void ** buff_ptr){
    *buff_ptr = malloc(size);
    return (*buff_ptr==NULL) & UALLOC_MALLOC_FAILED;
}

void heap_free(void ** buff_ptr){
    free(*buff_ptr);
    *buff_ptr=NULL;
}
