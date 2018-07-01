#pragma once

#include <random>
#include <algorithm>
#include <math.h>

extern std::random_device rd; // only used once to initialise (seed) engine
extern std::mt19937 rng; // random-number engine used (Mersenne-Twister in this case)

inline int randunifrange(int start, int stop) {
  std::uniform_int_distribution<int> uni(start, stop);
  return uni(rng);
}

inline double randunif_zero_one() {
  std::uniform_real_distribution<double> uni(0, 1);
  return uni(rng);
}
