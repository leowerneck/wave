#include <stdlib.h>
#include "wave.h"

int main(int argc, char **argv) {

  wave_params *params = parse_args(argc, argv);
  if(!params) {
    exit(1);
  }
  params_info(params);

  free(params);
  return 0;
}
