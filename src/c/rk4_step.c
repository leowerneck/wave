#include "wave.h"

void rk4_step(
    void rhs(const void *restrict, const int *restrict, const real *restrict, real *restrict),
    void bcs(const void *restrict, const int *restrict, real *restrict),
    const void *restrict params,
    const int *restrict n,
    rk4params_t *restrict rk4params,
    real *restrict y) {

  const int ntotal = NGFS * n[0] * n[1] * n[2];

  // RK4 is done in 4 steps:
  //
  // k1 = f(t     , y        )
  // k2 = f(t+dt/2, y+dt*k1/2)
  // k3 = f(t+dt/2, y+dt*k2/2)
  // k4 = f(t+dt  , y+dt*k3  )
  //
  // y -> y + (dt/6)*(k1 + 2*k2 + 2*k3 + k4)

  const real dt = rk4params->dt;
  real *k1 = rk4params->k1;
  real *k2 = rk4params->k2;
  real *k3 = rk4params->k3;
  real *k4 = rk4params->k4;
  real *ky = rk4params->ky;

  // First RK4 step
  rhs(params, n, y, k1);
  bcs(params, n, k1);
#pragma omp parallel for
  for(int i = 0; i < ntotal; i++) {
    ky[i] = y[i] + 0.5 * dt * k1[i];
  }

  // Second RK4 step
  rhs(params, n, ky, k2);
  bcs(params, n, k2);
#pragma omp parallel for
  for(int i = 0; i < ntotal; i++) {
    ky[i] = y[i] + 0.5 * dt * k2[i];
  }

  // Third RK4 step
  rhs(params, n, ky, k3);
  bcs(params, n, k3);
#pragma omp parallel for
  for(int i = 0; i < ntotal; i++) {
    ky[i] = y[i] + dt * k3[i];
  }

  // Fourth RK4 step
  rhs(params, n, ky, k4);
  bcs(params, n, k4);

  // Final RK4 step
#pragma omp parallel for
  for(int i = 0; i < ntotal; i++) {
    y[i] = y[i] + (dt / 6.0) * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
  }
}
