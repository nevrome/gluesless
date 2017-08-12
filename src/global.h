#include <Rcpp.h>
#include <string>

inline int randWrapper(int n) {
  return floor(unif_rand()*n);
}

inline int randunifrange(int start, int stop) {
  return (int)round(R::runif(start,stop));
}

inline int get_number_of_digits (int i) {
  return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}