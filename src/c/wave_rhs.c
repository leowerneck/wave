#include "wave.h"

void wave_rhs(
    const void *restrict params_in,
    const int *restrict n,
    const real *restrict gfs,
    real *restrict rhs ) {

  const waveparams_t *restrict params = (const waveparams_t *restrict)params_in;

  const real c2     = params->c2;
  const real invdx2 = params->invdx2;
  const real invdy2 = params->invdy2;
  const real invdz2 = params->invdz2;

#pragma omp parallel for collapse(3)
  for(int k=NG;k<n[2]-NG;k++) {
    for(int j=NG;j<n[1]-NG;j++) {
      for(int i=NG;i<n[0]-NG;i++) {
        // The wave equation:
        //
        // d^2u/dt^2 = c^2( d^2u/dx^2 + d^2u/dy^2 + d^2u/dz^2 )
        //
        // We can define:
        //
        // v = du/dt, which leads to the two equations:
        //
        // du/dt = v ,
        // dv/dt = (1/c^2)( d^2u/dx^2 + d^2u/dy^2 + d^2u/dz^2 )

        // Read the gridfunctions at (i, j, k)
        const real u = gfs[IDX(UUGF, i, j, k)];
        const real v = gfs[IDX(VVGF, i, j, k)];

        // Now read u at the stencil
        const real u_ip1 = gfs[IDX(UUGF, i+1, j, k)];
        const real u_im1 = gfs[IDX(UUGF, i-1, j, k)];
        const real u_jp1 = gfs[IDX(UUGF, i, j+1, k)];
        const real u_jm1 = gfs[IDX(UUGF, i, j-1, k)];
        const real u_kp1 = gfs[IDX(UUGF, i, j, k+1)];
        const real u_km1 = gfs[IDX(UUGF, i, j, k-1)];

        // Now compute the derivatives
        const real d2udx2 = ( u_ip1 - 2*u + u_im1 ) * invdx2;
        const real d2udy2 = ( u_jp1 - 2*u + u_jm1 ) * invdy2;
        const real d2udz2 = ( u_kp1 - 2*u + u_km1 ) * invdz2;

        // Now set the rhss
        rhs[IDX(UUGF, i, j, k)] = v;
        rhs[IDX(VVGF, i, j, k)] = c2 * ( d2udx2 + d2udy2 + d2udz2);
      }
    }
  }
}
