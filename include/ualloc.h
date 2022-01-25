#ifndef UNSALTED_UALLOC_H
#define UNSALTED_UALLOC_H

#include <stdint.h>
#include <stddef.h>

struct _linear_allocator {
    void * buffer;
    void * position;
    size_t size;
};

struct _stack_allocator {
    void * buffer;
    void * position;
    size_t size;
};

typedef struct _linear_allocator linear_allocator;
typedef struct _stack_allocator  stack_allocator; 

int8_t heap_alloc(size_t, void**);
void   heap_free(void**);

int8_t lin_alloc_init(size_t, linear_allocator *);
int8_t lin_alloc(size_t, linear_allocator *, void **);
void   lin_destroy(linear_allocator *);
void   lin_free_all(linear_allocator *);

int8_t stack_alloc_init(size_t, stack_allocator *);
int8_t stack_alloc(size_t, stack_allocator *, void **);
int8_t   stack_free(stack_allocator *);
void   stack_destroy(stack_allocator *);


#endif //UNSALTED_UALLOC_H
