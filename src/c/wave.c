#include <stdio.h>
#include <stdlib.h>
#include "wave.h"

int main(int argc, char *argv[]) {

  if(argc != 3) {
    fprintf(stderr, "Usage: ./wave <Nx> <Ny> <Nz>\n");
    exit(1);
  }

  const int Nx = atoi(argv[1]);
  const int Ny = atoi(argv[2]);
  const int Nz = atoi(argv[3]);

  const int ntotal[3] = { Nx + 2 * NG, Ny + 2 * NG, Nz + 2 * NG };
  const int size = ntotal[0] * ntotal[1] * ntotal[2];

  real *xyz[3] = {
    malloc(sizeof(real) * ntotal[0]),
    malloc(sizeof(real) * ntotal[1]),
    malloc(sizeof(real) * ntotal[2]),
  };
  real *gfs = malloc(sizeof(real) * size);

  wave_id(ntotal, xyz, gfs);

  for(int i = 0; i < 3; i++) {
    free(xyz[i]);
  }
  free(gfs);

  return 0;
}
