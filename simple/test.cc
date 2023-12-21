#include <iostream>
#include <functional>
#include <cstdlib>
#include <cmath>

namespace Loop {
void loop(const int imin, const int imax, const std::function<void(const int)>& f) {
  for(int i = imin; i < imax; i++) {
    f(i);
  }
}
} // namespace Loop

class Realvec {
  int n;
  double* data;

public:
  Realvec(int size) : n{ size }, data{ new double[size]{} } {}
  ~Realvec() {
    delete[] data;
  }

  double& operator[](int i) {
    return data[i];
  }

  double& operator()(int i) {
    return (*this)[i];
  }

  double& at(int i) {
    if(i < 0 || i >= n) {
      std::cerr << "Input index " << i << " not in range [0, " << n - 1 << "]\n";
      exit(1);
    }
    return (*this)[i];
  }
};

class Grid {
  int Nx, Ng, NxpNg, NxTotal;
  double xmin, xmax, dx;
  Realvec x_data, gridfunction_data;

public:
  Grid(const int Nx, const int Ng, const double xmin, const double xmax)
      : Nx{ Nx },
        Ng{ Ng },
        NxpNg{ Nx + Ng },
        NxTotal{ NxpNg + Ng },
        xmin{ xmin },
        xmax{ xmax },
        dx{ (xmax - xmin) / (Nx - 1) },
        x_data{ NxTotal },
        gridfunction_data{ 2 * NxTotal } {

    loop_everywhere([this](const int i) {
      this->x(i) = this->xmin + (i - this->Ng) * this->dx;
    });
  }

  void loop_interior(const std::function<void(const int)>& f) {
    Loop::loop(Ng, NxpNg, f);
  }

  void loop_everywhere(const std::function<void(const int)>& f) {
    Loop::loop(0, NxTotal, f);
  }

  double& u(const int i) {
    return gridfunction_data(i);
  }

  double& v(const int i) {
    return gridfunction_data(i + NxTotal);
  }

  double& x(const int i) {
    return x_data(i);
  }

  int nx() const {
    return Nx;
  }

  int nghost() const {
    return Ng;
  }

  int size() const {
    return NxTotal;
  }

  double x_max() const {
    return xmax;
  }

  double x_min() const {
    return xmin;
  }
};

void wave_set_initial_data(Grid& grid) {
  grid.loop_everywhere([&grid](const int i) {
    grid.u(i) = sin(grid.x(i));
    grid.v(i) = 0.0;
  });
}

int main(int argc, char* argv[]) {

  if(argc != 2) {
    std::cerr << "Correct usage is: ./test <Nx>\n";
    exit(1);
  }

  Grid grid(atoi(argv[1]), 2, -M_PI, M_PI);

  wave_set_initial_data(grid);

  grid.loop_everywhere([&grid](const int i) {
    std::cout << grid.x(i) << " " << grid.u(i) << "\n";
  });

  return 0;
}
