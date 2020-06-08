#pragma once

#include <stddef.h>

void* mymalloc(size_t size);
void myfree(void *ptr);
void report();

typedef struct __uheader_t {
    int magic;
    int size;
} uheader_t;

typedef struct __fheader_t {
    int magic;
    int size;
    struct __fheader_t* next;
} fheader_t;