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
//' @export
// [[Rcpp::export]]
std::string run(SEXP modell_builder, int steps = 100){

  // load modell builder
  Rcpp::S4 mb(modell_builder);

  SEXP graphstr = wrap(mb.slot("networkland_env"));
  std::string graphstring = Rcpp::as<std::string>(graphstr);


  // create environment
  Networkland* landofoz = new Networkland(
    graphstring
  );
  std::string floet = landofoz->export_graph();

  //double si = wrap(mb.slot("population_size"));
  double size = Rcpp::as<double>(mb.slot("population_size"));

  //create testpopulation
  Population* testpop = new Population(
    size
  );



  delete testpop;

  return floet;
}