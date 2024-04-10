#include <stdio.h>
#include "wave.h"

void params_info(wave_params *params) {
  printf("Wave parameters:\n");
  printf("  Number of dimensions: %d\n", params->dim);

  switch(params->dim) {
    case 1:
      printf("  Interior grid size: %d\n", params->nx);
      printf(
          "  Total grid size: %d (including %d ghost zones on each side)\n", params->ntx,
          params->ngx);
      break;
    case 2:
      printf("  Interior grid size: %d x %d\n", params->nx, params->ny);
      printf(
          "  Total grid size: %d x %d (including %d ghost zones on each side)\n", params->ntx,
          params->nty, params->ngx);
      break;
    case 3:
      printf("  Interior grid size: %d x %d x %d\n", params->nx, params->ny, params->nz);
      printf(
          "  Total grid size: %d x %d x %d (including %d ghost zones on each side)\n", params->ntx,
          params->nty, params->ntz, params->ngx);
      break;
  }
}
