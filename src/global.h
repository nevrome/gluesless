#include <Rcpp.h>
#include <string>

inline int randWrapper(int n) {
  return floor(unif_rand()*n);
}

inline int randunifrange(int start, int stop) {
  return (int)round(R::runif(start,stop));
}