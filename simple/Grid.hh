#ifndef GRID_HH__
#define GRID_HH__

#include "Realvec.hh"
#include "Loop.hh"

class Grid {
  size_t Nx{ 0 }, Ng{ 0 }, NxTotal{ 0 };
  double dx{};
  Realvec x_data;
  Realvec gridfunction_data;

public:
  Grid(const size_t Nx, const size_t Ng, const double& xmin, const double& xmax)
      : Nx{ Nx },
        Ng{ Ng },
        NxTotal{ Nx + 2 * Ng },
        dx{ (xmax - xmin) / (Nx - 1) },
        x_data{ NxTotal },
        gridfunction_data{ NxTotal } {

    Loop::loop1d_everywhere(Nx, Ng, [=](const size_t i) -> void { x_data[i] = xmin + dx * i; });
  }

  const double x(const size_t i) const {
    return x_data[i];
  }

  void init(const size_t direction, const double min, const double max) {}
};

#endif // GRID_HH__
