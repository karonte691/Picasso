
#pragma once

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define P_PI 3.14159265358979323846f
#define P_PI_2 2.0f * P_PI
#define P_HALF_PI 0.5f * P_PI
#define P_QUARTER_PI 0.25f * P_PI
#define P_ONE_OVER_PI 1.0f / P_PI
#define P_ONE_OVER_TWO_PI 1.0f / P_PI_2
#define P_SQRT_TWO 1.41421356237309504880f
#define P_SQRT_THREE 1.73205080756887729352f
#define P_SQRT_ONE_OVER_TWO 0.70710678118654752440f
#define P_SQRT_ONE_OVER_THREE 0.57735026918962576450f
#define P_DEG2RAD_MULTIPLIER P_PI / 180.0f
#define P_RAD2DEG_MULTIPLIER 180.0f / P_PI

// The multiplier to convert seconds to milliseconds.
#define P_SEC_TO_MS_MULTIPLIER 1000.0f

// The multiplier to convert milliseconds to seconds.
#define P_MS_TO_SEC_MULTIPLIER 0.001f

// A huge number that should be larger than any valid number used.
#define P_INFINITY 1e30f

// Smallest positive number where 1.0 + FLOAT_EPSILON != 0
#define P_FLOAT_EPSILON 1.192092896e-07f

#endif