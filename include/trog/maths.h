#ifndef MATHS_H
#define MATHS_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define tr_square(x) ((x) * (x))

#define tr_cube(x) ((x) * (x) * (x))

inline uint32_t tr_mini(const uint32_t x, const uint32_t y) {
        return (x < y) ? x : y;
}

inline uint64_t tr_mind(const uint64_t x, const uint64_t y) {
        return (x < y) ? x : y;
}

inline uint32_t tr_maxi(const uint32_t x, const uint32_t y) {
        return (x > y) ? x : y;
}
inline uint64_t tr_maxd(const uint64_t x, const uint64_t y) {
        return (x > y) ? x : y;
}

#ifdef __cplusplus
}
#endif

#endif // MATHS_H
