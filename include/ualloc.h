#ifndef UNSALTED_UALLOC_H
#define UNSALTED_UALLOC_H

#include <stddef.h>

#define UALLOC_SUCCESS 0
#define UALLOC_MALLOC_FAILED 1
#define UALLOC_ALLOCATOR_INSUFFICIENT_SPACE 2
#define UALLOC_STACK_EMPTY 3

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

int heap_alloc(size_t, void**);
void   heap_free(void**);

int lin_alloc_init(size_t, linear_allocator *);
int lin_alloc(size_t, linear_allocator *, void **);
void   lin_destroy(linear_allocator *);
void   lin_free_all(linear_allocator *);

int stack_alloc_init(size_t, stack_allocator *);
int stack_alloc(size_t, stack_allocator *, void **);
int   stack_free(stack_allocator *);
void   stack_destroy(stack_allocator *);


#endif //UNSALTED_UALLOC_H
