#include <Rcpp.h>
#include <cstdlib>
#include <math.h>
#include "Population.h"

using namespace Rcpp;

//' run model
//'
//' @description
//' test
//'
//' @details
//' test
//'
//' @param steps test
//'
//' @return
//' test
//'
//' @examples
//' run()
//'
//' @export
// [[Rcpp::export]]
double run(int steps = 100){
  Population* testpop = new Population(100, 0.1, 0.5);

  Rcout << testpop->size_get() << std::endl;

  for (int t = 1; t <= steps; t++) {
    testpop->develop();
  }

  double res = testpop->size_get();

  delete testpop;

  return res;
}