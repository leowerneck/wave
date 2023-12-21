#ifndef REALVEC_HH__
#define REALVEC_HH__

#include <iostream>
#include <cstdlib>

class Realvec {
  size_t n;
  double* data;

public:
  Realvec(size_t size) : n{ size }, data{ new double[size]{} } {}
  ~Realvec() {
    delete[] data;
  }

  double& operator[](size_t i) {
    return data[i];
  }

  double& operator()(size_t i) {
    return (*this)[i];
  }

  double& at(size_t i) {
    if(i < 0 || i >= n) {
      std::cerr << "Input index " << i << " not in range [0, " << n - 1 << "]\n";
      exit(1);
    }
    return (*this)[i];
  }
};

#endif // REALVEC_HH__
