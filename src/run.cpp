#include <Rcpp.h>
#include <cstdlib>
#include <math.h>

#include "Idea.h"
#include "Networkland.h"
#include "Timeline.h"

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
//'
//' @return
//' test
//'
//' @export
// [[Rcpp::export]]
SEXP run(SEXP modell_builder){

  // load modell builder
  Rcpp::S4 mb(modell_builder);

  // create start environment
  SEXP graphstr = wrap(mb.slot("networkland_env"));
  std::string graphstring = Rcpp::as<std::string>(graphstr);

  // Realwelt
  Networkland* real = new Networkland(graphstring);

  // Geistwelt
  Aether* overmind = new Aether(real);

  // Zeit
  Timeline* thyme = new Timeline(overmind);

  // develop
  for (int i = 0; i < 100; i++) {
    thyme->develop(overmind);
  }

  List res = thyme->export_as_R_list();

  return res;
}