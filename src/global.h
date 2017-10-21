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

// https://stackoverflow.com/questions/1577475/c-sorting-and-keeping-track-of-indexes
template <typename T>
std::vector<size_t> sort_indexes(const std::vector<T> &v) {

  // initialize original index locations
  std::vector<size_t> idx(v.size());
  iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  sort(idx.begin(), idx.end(),
       [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

  return idx;
}