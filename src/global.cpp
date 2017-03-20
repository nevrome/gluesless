#include <Rcpp.h>
#include <string>
#include <algorithm>

# include "global.h"

using namespace Rcpp;
using namespace std;

int randunif(int start, int stop) {
  int x = (int)round(R::runif(start,stop));
  return x;
}

// http://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
std::string random_string(size_t length) {
  auto randchar = []() -> char {
    const char charset[] =
      "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";
    const int max_index = (sizeof(charset) - 2);
    return charset[randunif(0, max_index)];
  };
  std::string str(length, 'a');
  std::generate_n(str.begin(), length, randchar);
  return str;
}