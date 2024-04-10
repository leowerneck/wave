#ifndef WAVE_H_
#define WAVE_H_

#include <stdint.h>

// Wave parameters struct
typedef struct wave_params {
  uint8_t dim;            // number of dimensions
  uint8_t ngx, ngy, ngz;  // number of ghostzones in each direction
  uint16_t nx, ny, nz;    // number of interior gridpoints in each direction
  uint16_t ntx, nty, ntz; // number of total gridpoints in each direction
} wave_params;

// Function prototypes
void usage(void);
wave_params *parse_args(int argc, char **argv);
void params_info(wave_params *params);

#endif // WAVE_H_
