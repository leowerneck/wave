#include "Grid.hh"

int main(int argc, char *argv[]) {

  if(argc != 4) {
    std::cerr << "Correct usage is ./wave <Nx> <xmin> <xmax>\n";
    return 1;
  }

  const int Nx = atoi(argv[1]);
  const int Ng = 2;
  const double xmin = strtod(argv[2], NULL);
  const double xmax = strtod(argv[3], NULL);

  Grid grid{Nx, Ng, xmin, xmax};

  return 0;
}
