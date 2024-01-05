#ifndef SIMPLICITY_BOUNDED_H
#define SIMPLICITY_BOUNDED_H

#include <stdbool.h>
#include <stdint.h>

typedef uint_least32_t ubounded;
#define UBOUNDED_MAX UINT32_MAX

/*
Windows.h includes minwindef.h which defines a "max" macro that causes the
following function definition to fail compilation with "error: C2059" on MSVC.

https://github.com/tpn/winsdk-10/blob/9b69fd26ac0c7d0b83d378dba01080e93349c2ed/Include/10.0.10240.0/shared/minwindef.h#L193
*/
#undef max

static inline ubounded max(uint_least32_t x, uint_least32_t y) {
  return x <= y ? y : x;
}

/* Returns min(x + y, UBOUNDED_MAX) */
static inline ubounded bounded_add(ubounded x, ubounded y) {
  return UBOUNDED_MAX < x ? UBOUNDED_MAX
       : UBOUNDED_MAX - x < y ? UBOUNDED_MAX
       : x + y;
}

/* *x = min(*x + 1, UBOUNDED_MAX) */
static inline void bounded_inc(ubounded* x) {
  if (*x < UBOUNDED_MAX) (*x)++;
}

/* 'pad(false, a, b)' computes the PADL(a, b) function.
 * 'pad( true, a, b)' computes the PADR(a, b) function.
 */
static inline ubounded pad(bool right, ubounded a, ubounded b) {
  return max(a, b) - (right ? b : a);
}

static const ubounded overhead = 100 /* milli weight units */;
#endif
