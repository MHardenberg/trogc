#ifndef MATHS_H
#define MATHS_H
#include <stdint.h>

inline uint32_t f_mini(const uint32_t x, const uint32_t y){
return (x < y)? x : y;
}

inline uint64_t f_mind(const uint64_t x, const uint64_t y){
return (x < y)? x : y;
}

inline uint32_t f_maxi(const uint32_t x, const uint32_t y){
return (x > y)? x : y;
}
inline uint64_t f_maxd(const uint64_t x, const uint64_t y){
return (x > y)? x : y;
}

#endif // MATHS_H
