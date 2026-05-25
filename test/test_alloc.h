#ifndef _TEST_ALLOC
#define _TEST_ALLOC
#include <trog.h>
#include <trog/mem/alloc.h>
#include <trog/mem/scratchpad.h>
#include <test.h>

#define PAGE_SIZE 4096

static void test_tr_arenaPush() {
        tr_alloc arena;
        tr_allocCreate(&arena, ALLOC_ARENA);

        int res = 0;
        for (size_t i = 0; i < 100; ++i) {
                char *mems = tr_allocPush(&arena, PAGE_SIZE);
                if (mems == NULL) {
                        ++res;
                }
                if (arena.alloc.allocArena.offset <= i * PAGE_SIZE) {
                        ++res;
                }
        }
        TEST_ZERO(res);

        tr_allocClear(&arena);
        TEST_TRUE((arena.alloc.allocArena.offset == 0));
        tr_allocDestroy(&arena);
}

static void test_tr_arenaPushZero() {
        tr_alloc arena;
        tr_allocCreate(&arena, ALLOC_ARENA);

        int res = 0;
        for (size_t i = 0; i < 100; ++i) {
                char *mems = tr_allocPushZero(&arena, PAGE_SIZE);
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

        TEST_ZERO(res);
        tr_allocClear(&arena);
        TEST_TRUE((arena.alloc.allocArena.offset == 0));
        tr_allocDestroy(&arena);
}

static void test_tr_arenaPushMany() {
        tr_alloc arena;
        tr_allocCreate(&arena, ALLOC_ARENA);

        size_t Gigs = 1LL * 1024LL * 1024LL * 1024LL;
        char *mems = tr_allocPushZero(&arena, Gigs);
        TEST_TRUE((mems != NULL));
        TEST_TRUE((arena.alloc.allocArena.offset >= Gigs));

        tr_allocClear(&arena);
        TEST_TRUE((arena.alloc.allocArena.offset == 0));
        tr_allocDestroy(&arena);
}

static void test_tr_ScratchPad() {
        tr_alloc arena;
        tr_allocCreate(&arena, ALLOC_ARENA);
        tr_ScratchPad *pad = tr_ScratchPadCreate(&arena, 1024);
        TEST_TRUE((pad->buffer != NULL));

        // push
        char *str = tr_ScratchPadPush(pad, 64);
        TEST_TRUE((str != NULL));
        TEST_TRUE((pad->offset >= 64));

        // push too much
        size_t offsetBefore = pad->offset;
        void *dest = tr_ScratchPadPush(pad, 2048);
        TEST_EQUAL(dest, NULL);
        TEST_EQUAL(offsetBefore, pad->offset);

        // clear
        tr_ScratchPadClear(pad);
        TEST_EQUAL(pad->offset, 0);
}

void test_tr_alloc() {
        test_tr_arenaPush();
        test_tr_arenaPushMany();
        test_tr_arenaPushZero();
        test_tr_ScratchPad();
}
#endif //_TEST_ALLOC
