#ifndef MATHS_H
#define MATHS_H
#include <stdint.h>

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

#endif // MATHS_H
