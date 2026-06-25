#ifndef _TROGCU
#define _TROGCU

#include <cuda_runtime.h>
#include <trogLogging.h>

#define threadsPerBlock 256

#ifdef _DEBUG
#define trogCuErrcheck                                                         \
        do {                                                                   \
                cudaError_t err = cudaGetLastError();                          \
                if (err != cudaSuccess) {                                      \
                        LOGERR(stderr, "CUDA Kernel Launch Error: %s\n",       \
                               cudaGetErrorString(err));                       \
                        \                                                      \
                }                                                              \
                while {                                                        \
                        0                                                      \
                }

#else
#define trogCuErrcheck
#endif
#endif // _TROGCU
