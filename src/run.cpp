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
//' @param popdevel test
//' @param steps test
//'
//' @return
//' test
//'
//' @examples
//' f <- function(size,birthrate,deathrate) {
//'   res <- size + size*birthrate*2 - size*deathrate*2
//'   return(res)
//' }
//'
//' run(f)
//'
//' @export
// [[Rcpp::export]]
double run(Function popdevel, int steps = 100){

  //create testpopulation
  Population* testpop = new Population(100, 0.1, 0.05);

  Rcout << testpop->size_get() << std::endl;

  for (int t = 1; t <= steps; t++) {
    testpop->develop(popdevel);
  }

  double res = testpop->size_get();

  delete testpop;

  return res;
}