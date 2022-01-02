#ifndef UNSALTED_UALLOC_H
#define UNSALTED_UALLOC_H

struct _linear_allocator {
    void * buffer;
    void * position;
    size_t size;
};

typedef _linear_allocator linear_allocator;

int8_t heap_alloc(size_t, void**);
void   heap_free(void**);

int8_t lin_alloc_init(size_t, linear_allocator *);
int8_t lin_alloc(size_t, linear_allocator *, void **);
void lin_free(linear_allocator *);
void lin_clear(linear_allocator *);


#endif //UNSALTED_UALLOC_H
