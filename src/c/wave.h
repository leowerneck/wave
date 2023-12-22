#ifndef WAVE_H_
#define WAVE_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SINGLE 0
#define DOUBLE 1
#define PRECISION SINGLE

#if PRECISION == SINGLE

#define real float
#define sinr sinf
#define cosr cosf
#define absr fabsf

#elif PRECISION == DOUBLE

#define real double
#define sinr sin
#define cosr cos
#define absr fabs

#else
#error "Unsupported precision"
#endif

typedef struct rk4params_t {
  real dt, *k1, *k2, *k3, *k4, *ky;
} rk4params_t;

typedef struct waveparams_t {
  real c, c2, dx, dy, dz, invdx, invdy, invdz, invdx2, invdy2, invdz2;
} waveparams_t;

#define UUGF 0
#define VVGF 1
#define NGFS 2

#define NG 1

#define IDX(gf, i, j, k) ((i) + n[0] * ((j) + n[1] * ((k) + n[2] * (gf))))

#endif /* WAVE_H_ */
