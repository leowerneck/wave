#ifndef GRIDFUNCTION_HH__
#define GRIDFUNCTION_HH__

#include <cstdint>
#include <cstdlib>
#include <iostream>

template <uint16_t dimension = 3>
class Gridfunction {
  uint16_t Nx{ 0 }, Ny{ 0 }, Nz{ 0 }, Ng{ 0 };
  uint64_t NxTotal{ 0 }, NyTotal{ 0 }, NzTotal{ 0 };
  uint64_t NxNyTotal{ 0 }, NxNyNzTotal{ 0 };
  double* data{ nullptr };

public:
  Gridfunction(const uint16_t Nx, const uint16_t Ng) {

    static_assert(dimension == 1, "This ctor requires 1d gridfunctions (i.e., Gridfunction<1>)");

    this->Nx = Nx;
    this->Ng = Ng;

    NxTotal = Nx + 2 * Ng;
    NxNyNzTotal = NxTotal;

    data = new double[NxNyNzTotal]{};
  }

  Gridfunction(const uint16_t Nx, const uint16_t Ny, const uint16_t Ng) {

    static_assert(dimension == 2, "This ctor requires 2d gridfunctions (i.e., Gridfunction<2>)");

    this->Nx = Nx;
    this->Ny = Ny;
    this->Ng = Ng;

    NxTotal = Nx + 2 * Ng;
    NyTotal = Ny + 2 * Ng;

    NxNyTotal = NxTotal * NyTotal;
    NxNyNzTotal = NxNyTotal;

    data = new double[NxNyNzTotal]{};
  }

  Gridfunction(const uint16_t Nx, const uint16_t Ny, const uint16_t Nz, const uint16_t Ng) {

    static_assert(dimension == 3, "This ctor requires 3d gridfunctions (i.e., Gridfunction<3>)");

    this->Nx = Nx;
    this->Ny = Ny;
    this->Nz = Nz;
    this->Ng = Ng;

    NxTotal = Nx + 2 * Ng;
    NyTotal = Ny + 2 * Ng;
    NzTotal = Nz + 2 * Ng;
    NyTotal = NzTotal = 1;

    NxNyTotal = NxTotal * NyTotal;
    NxNyNzTotal = NxNyTotal * NzTotal;

    data = new double[NxNyNzTotal]{};
  }

  ~Gridfunction() {
    delete[] data;
  }

  uint64_t size() const {
    return NxNyNzTotal;
  }

  uint16_t size(const uint8_t direction) const {
    return NxTotal * (direction == 0) + NyTotal * (direction == 1) + NzTotal * (direction == 2);
  }

  uint16_t nghosts() const {
    return Ng;
  }

  double* begin() const {
    return data;
  }

  double* end() const {
    return data + NxNyNzTotal - 1;
  }

  double& operator[](const uint16_t i) {
    return data[i];
  }

  double& operator()(const uint16_t i) {
    return (*this)[i];
  }

  double& operator()(const uint16_t i, const uint16_t j) {
    static_assert(dimension < 2, "Dimension must be at least 2");
    return (*this)[i + NxTotal * j];
  }

  double& operator()(const uint16_t i, const uint16_t j, const uint16_t k) {
    static_assert(dimension < 3, "Dimension must be at least 3");
    return (*this)[i + NxTotal * j + NxNyTotal * k];
  }

  double& at(const uint16_t i) {
    const uint16_t Nmax = NxTotal * (dimension == 1) + NxNyTotal * (dimension == 2)
                        + NxNyNzTotal * (dimension == 3);
    if(i < 0 || i >= Nmax) {
      std::cerr << "Out of bound x-index: " << i << " not in [0, " << Nmax - 1 << "]\n";
      exit(1);
    }

    (*this)(i);
  }

  double& at(const uint16_t i, const uint16_t j) {
    static_assert(dimension < 2, "Dimension must be at least 2");

    if(i < 0 || i >= NxTotal) {
      std::cerr << "Out of bound x-index: " << i << " not in [0, " << NxTotal - 1 << "]\n";
      exit(1);
    }

    if(j < 0 || j >= NyTotal) {
      std::cerr << "Out of bound y-index: " << j << " not in [0, " << NyTotal - 1 << "]\n";
      exit(1);
    }

    (*this)(i, j);
  }

  double& at(const uint16_t i, const uint16_t j, const uint16_t k) {
    static_assert(dimension < 3, "Dimension must be at least 3");

    if(i < 0 || i >= NxTotal) {
      std::cerr << "Out of bound x-index: " << i << " not in [0, " << NxTotal - 1 << "]\n";
      exit(1);
    }
    if(j < 0 || j >= NyTotal) {
      std::cerr << "Out of bound y-index: " << j << " not in [0, " << NyTotal - 1 << "]\n";
      exit(1);
    }
    if(k < 0 || k >= NzTotal) {
      std::cerr << "Out of bound z-index: " << k << " not in [0, " << NzTotal - 1 << "]\n";
      exit(1);
    }

    (*this)(i, j, k);
  }
};

#endif // GRIDFUNCTION_HH__
