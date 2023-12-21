#ifndef LOOP_HH__
#define LOOP_HH__

#include <cstddef>

namespace Loop {

void loop1d(const size_t imin, const size_t imax, void (*f)(const size_t)) {
  for(size_t i = imin; i < imax; i++) {
    f(i);
  }
}

void loop1d_everywhere(const size_t n, const size_t nghosts, void (*f)(const size_t)) {
  loop1d(0, n, f);
}

void loop1d_interior(const size_t n, const size_t nghosts, void (*f)(const size_t)) {
  loop1d(nghosts, n + nghosts, f);
}

} // namespace Loop

#endif // LOOP_HH__
