#include <random>
#include <algorithm>
#include <math.h>

inline std::random_device rd; // only used once to initialise (seed) engine
inline std::mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)

inline int randunifrange(int start, int stop) {
  std::uniform_int_distribution<int> uni(start, stop); // guaranteed unbiased
  return uni(rng);
}
