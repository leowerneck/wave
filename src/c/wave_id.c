#include "wave.h"

void wave_id(
    const int *restrict n,
    const real *restrict xx[3],
    real *restrict gfs ) {

#pragma omp parallel for collapse(3)
  for(int k=0;k<n[2];k++) {
    for(int j=0;j<n[1];j++) {
      for(int i=0;i<n[0];i++) {
        // We want: u(0, x, y, z) = sin(x) + cos(y)
        //          v(0, x, y, z) = 0
        gfs[IDX(UUGF, i, j, k)] = sinr(xx[0][i]) + cosr(xx[1][j]);
        gfs[IDX(VVGF, i, j, k)] = 0;
      }
    }
  }
}
