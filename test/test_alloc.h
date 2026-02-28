#ifndef _TEST_ALLOC
#define _TEST_ALLOC
#include "forge.h"
#include "forge/mem/alloc.h"
#include <test.h>

#define PAGE_SIZE 4096

static void test_f_arenaPush() {
        f_alloc arena;
        f_allocCreate(&arena, ALLOC_ARENA);

        int res = 0;
        for (size_t i = 0; i < 100; ++i) {
                char *mems = f_allocPush(&arena, PAGE_SIZE);
                if (mems == NULL) {
                        ++res;
                }
                if (arena.alloc.allocArena.offset <= i * PAGE_SIZE) {
                        ++res;
                }
        }
        TEST_ZERO(res);

        f_allocClear(&arena);
        TEST_TRUE((arena.alloc.allocArena.offset == 0));
        f_allocDestroy(&arena);
}

static void test_f_arenaPushZero() {
        f_alloc arena;
        f_allocCreate(&arena, ALLOC_ARENA);

        int res = 0;
        for (size_t i = 0; i < 100; ++i) {
                char *mems = f_allocPushZero(&arena, PAGE_SIZE);
                if (mems == NULL) {
                        LOGERROR("NULL output\n");
                        ++res;
                }
                if (arena.alloc.allocArena.offset <= i * PAGE_SIZE) {
                        ++res;
                        LOGERROR("Arena offset error\n");
                }
                for (size_t j = 0; j < PAGE_SIZE; ++j) {
                        if (mems[j] != 0) {
                                res++;
                        }
                }
        }

        f_allocClear(&arena);
        TEST_TRUE((arena.alloc.allocArena.offset == 0));
        f_allocDestroy(&arena);
}

static void test_f_arenaPushMany() {
        f_alloc arena;
        f_allocCreate(&arena, ALLOC_ARENA);

        size_t lotsOfGigs = 10LL * 1024LL * 1024LL * 1024LL;
        char *mems = f_allocPushZero(&arena, lotsOfGigs);
        TEST_TRUE((mems != NULL));
        TEST_TRUE((arena.alloc.allocArena.offset >= lotsOfGigs));

        f_allocClear(&arena);
        TEST_TRUE((arena.alloc.allocArena.offset == 0));
        f_allocDestroy(&arena);
}

void test_f_alloc() {
        test_f_arenaPush();
        test_f_arenaPushMany();
        test_f_arenaPushZero();
}
#endif //_TEST_ALLOC
