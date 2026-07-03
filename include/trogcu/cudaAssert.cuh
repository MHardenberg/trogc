#ifndef _CUDA_ASSERT
#define _CUDA_ASSERT

#ifdef _DEBUG
#ifdef __CUDA_ARCH__
#define tr_cudaAssert(condition)                                               \
        if (!(condition)) {                                                    \
                asm("trap;");                                                  \
        }

#else
#define tr_cudaAssert(condition)                                               \
        if (!(condition)) {                                                    \
                printf("Assertion %s failed!\n", #condition);                  \
                asm("trap;");                                                  \
        }
#endif

#else
#define tr_cudaAssert(condition)
#endif

#endif // _CUDA_ASSERT
