#ifndef EZMATH_H
#define EZMATH_H

#include <math.h>
#include <float.h>
#include <stdlib.h> // for abs() etc.
#include <limits.h> // For INT_MAX / UINT_MAX

typedef float				f32;
typedef double				f64;
typedef signed int		s32;

inline f32 squareroot(const f32 f)
{
        return sqrtf(f);
}

inline f64 squareroot(const f64 f)
{
        return sqrt(f);
}

inline s32 squareroot(const s32 f)
{
        return static_cast<s32>(squareroot(static_cast<f32>(f)));
}

// calculate: 1 / sqrt ( x )
inline f64 reciprocal_squareroot(const f64 x)
{
        return 1.0 / sqrtf(x);
}

#endif // MY_MATH_H
