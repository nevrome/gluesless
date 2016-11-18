#define _USE_MATH_DEFINES

#include <Rcpp.h>
#include <cstdlib>
#include <math.h>

using namespace Rcpp;

//' cheesecake!
//'
//' @description
//' test
//'
//' @details
//' test
//'
//' @param i test
//'
//' @return
//' test
//'
//' @examples
//' cheesecake()
//'
//' @export
// [[Rcpp::export]]
bool cheesecake(int i = 1){
  Rcout << "cheesecake" << std::endl;
  return true;
}