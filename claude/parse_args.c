#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"

wave_params *parse_args(int argc, char **argv) {
  wave_params *params = malloc(sizeof(wave_params));
  if(!params) {
    fprintf(stderr, "Error: failed to allocate memory\n");
    return NULL;
  }

  params->dim = 0;
  params->ngx = params->ngy = params->ngz = 2;
  params->nx = params->ny = params->nz = 0;

  for(int i = 1; i < argc; i++) {
    if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      usage();
      free(params);
      return NULL;
    }
    else if(strncmp(argv[i], "-nx", 3) == 0) {
      if(argv[i][3] == '=') {
        params->nx = atoi(argv[i] + 4);
      }
      else if(i + 1 < argc) {
        params->nx = atoi(argv[++i]);
      }
      else {
        fprintf(stderr, "Error: missing value for -nx. Use -h for usage information.\n");
        free(params);
        return NULL;
      }
      params->dim++;
    }
    else if(strncmp(argv[i], "-ny", 3) == 0) {
      if(argv[i][3] == '=') {
        params->ny = atoi(argv[i] + 4);
      }
      else if(i + 1 < argc) {
        params->ny = atoi(argv[++i]);
      }
      else {
        fprintf(stderr, "Error: missing value for -ny. Use -h for usage information.\n");
        free(params);
        return NULL;
      }
      params->dim++;
    }
    else if(strncmp(argv[i], "-nz", 3) == 0) {
      if(argv[i][3] == '=') {
        params->nz = atoi(argv[i] + 4);
      }
      else if(i + 1 < argc) {
        params->nz = atoi(argv[++i]);
      }
      else {
        fprintf(stderr, "Error: missing value for -nz. Use -h for usage information.\n");
        free(params);
        return NULL;
      }
      params->dim++;
    }
    else {
      fprintf(stderr, "Warning: ignoring unknown argument '%s'\n", argv[i]);
    }
  }

  if(params->dim == 0) {
    free(params);
    return NULL;
  }

  switch(params->dim) {
    case 1:
      params->nx = params->nx + params->ny + params->nz;
      break;
    case 2:
      params->nx = params->nx ? params->nx : params->nz;
      params->ny = params->ny ? params->ny : params->nz;
      break;
    case 3:
      break;
    default:
      free(params);
      return NULL;
  }

  params->ntx = params->nx ? params->nx + 2 * params->ngx : 0;
  params->nty = params->ny ? params->ny + 2 * params->ngy : 0;
  params->ntz = params->nz ? params->nz + 2 * params->ngz : 0;

  return params;
}
