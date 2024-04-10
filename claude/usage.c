#include <stdio.h>

void usage(void) {
  printf("Usage: wave [options]\n");
  printf("Options:\n");
  printf("  -h, --help    Display this help message and exit\n");
  printf("  -nx=<value>   Number of grid points in the x-direction\n");
  printf("  -ny=<value>   Number of grid points in the y-direction\n");
  printf("  -nz=<value>   Number of grid points in the z-direction\n");
}
