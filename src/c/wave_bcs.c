#include "wave.h"

void wave_bcs(const void *restrict params_in, const int *restrict n, real *restrict gfs) {

  // Apply periodic boundary conditions.
  //
  // In the x-direction, this means:
  // f(0     , j, k) = f(n[0]-2, j, k)
  // f(n[0]-1, j, k) = f(1     , j, k)
#pragma omp parallel for collapse(3)
  for(int gf = 0; gf < NGFS; gf++) {
    for(int k = 0; k < n[2]; k++) {
      for(int j = 0; j < n[1]; j++) {
        gfs[IDX(gf, 0, j, k)] = gfs[IDX(gf, n[0] - 2, j, k)];
        gfs[IDX(gf, n[0] - 1, j, k)] = gfs[IDX(gf, 1, j, k)];
      }
    }
  }

  // In the y-direction, this means:
  // f(i, 0     , k) = f(i, n[1]-2, k)
  // f(i, n[1]-1, k) = f(i, 1     , k)
#pragma omp parallel for collapse(3)
  for(int gf = 0; gf < NGFS; gf++) {
    for(int k = 0; k < n[2]; k++) {
      for(int i = 0; i < n[0]; i++) {
        gfs[IDX(gf, i, 0, k)] = gfs[IDX(gf, i, n[1] - 2, k)];
        gfs[IDX(gf, i, n[1] - 1, k)] = gfs[IDX(gf, i, 1, k)];
      }
    }
  }

  // In the z-direction, this means:
  // f(i, j, 0     ) = f(i, j, n[1]-2)
  // f(i, j, n[2]-1) = f(i, j, 1     )
#pragma omp parallel for collapse(3)
  for(int gf = 0; gf < NGFS; gf++) {
    for(int j = 0; j < n[1]; j++) {
      for(int i = 0; i < n[0]; i++) {
        gfs[IDX(gf, i, j, 0)] = gfs[IDX(gf, i, j, n[2] - 2)];
        gfs[IDX(gf, i, j, n[2] - 1)] = gfs[IDX(gf, i, j, 1)];
      }
    }
  }
}
