#include <string>

inline int randWrapper(int n) {
  return floor(unif_rand()*n);
}

int randunifrange(int start, int stop);
std::string random_string(size_t length);