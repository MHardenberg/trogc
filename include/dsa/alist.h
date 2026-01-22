#ifndef ALIST_H
#define ALIST_H

#include "../forge.h"
typedef struct {
        size_t size;
        size_t capacity;
        uint8_t typeSize;
        void *data;
} alist;

void forge_alist_create(alist *dest, uint8_t typeSize, size_t capacity) {
        dest->data = 0;
        dest->capacity = capacity;
}

#endif // ALIST_H
