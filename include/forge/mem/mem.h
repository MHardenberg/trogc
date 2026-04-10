#ifndef MEM_H
#define MEM_H

#include <forge.h>
#define PAGE_SIZE 4096
#define DEFAULT_ALIGNMENT (2 * sizeof(void *))

static inline uintptr_t f_alignForward(uintptr_t ptr) {
        assert(!(DEFAULT_ALIGNMENT % 2));
        uintptr_t modulo = ptr & (uintptr_t)(DEFAULT_ALIGNMENT - 1);
        if (modulo != 0) {
                ptr += DEFAULT_ALIGNMENT - modulo;
        }
        return ptr;
}

static inline size_t f_alignPages(size_t bytes) {
        return (bytes % PAGE_SIZE) ? PAGE_SIZE * (bytes / PAGE_SIZE + 1)
                                   : bytes;
}

#endif // MEM_H
