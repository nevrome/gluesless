#include <Rcpp.h>
#include <cstdlib>
#include <math.h>
#include "Population.h"
#include "Networkland.h"

using namespace Rcpp;

//' run model
//'
//' @description
//' test
//'
//' @details
//' test
//'
//' @param modell_builder test
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
//' test_builder <- new(
//'   "modell_builder",
//'   pop_size = 200,
//'   pop_birthrate = 0.01,
//'   pop_deathrate = 0.005,
//'   pop_develop_udef_decision = FALSE,
//'   pop_develop_udef = f
//' )
//'
//' run(test_builder)
//'
//' @export
// [[Rcpp::export]]
std::string run(SEXP modell_builder, int steps = 100){

  // env test
  Networkland* landofoz = new Networkland();
  std::string floet = landofoz->export_graph();

  Rcpp::S4 mb(modell_builder);

  //create testpopulation
  Population* testpop = new Population(
    mb.slot("pop_size"),
    mb.slot("pop_birthrate"),
    mb.slot("pop_deathrate")
  );

  Rcout << testpop->size_get() << std::endl;

  for (int t = 1; t <= steps; t++) {
    if (mb.slot("pop_develop_udef_decision")) {
      testpop->develop();
    } else {
      testpop->develop_udef(mb.slot("pop_develop_udef"));
    }
  }

  double res = testpop->size_get();

  delete testpop;

  //double res = 1.0;

  return floet;
}