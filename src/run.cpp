#include <Rcpp.h>
#include <cstdlib>
#include <math.h>

#include "Idea.h"
#include "Networkland.h"
#include "Timeline.h"

using namespace Rcpp;

//' run model
//'
//' General run method. Something like the main function of a usual
//' c++-program. Runs model with input parameters and gives results
//' directly back to R.
//'
//' @param model_builder model_builder-object with parameters
//'
//' @return
//' List with different diagnostic values
//'
//' @export
// [[Rcpp::export]]
SEXP run(SEXP model_builder){

  // load modell builder
  Rcpp::S4 mb(model_builder);

  // create start environment
  SEXP graphstr = wrap(mb.slot("networkland_env"));
  std::string graphstring = Rcpp::as<std::string>(graphstr);
  SEXP iterations = wrap(mb.slot("number_iterations"));
  int iter = Rcpp::as<int>(iterations);

  // Realwelt
  Networkland* real = new Networkland(graphstring);

  // Geistwelt
  Aether* overmind = new Aether(real);

  // Zeit
  Timeline* thyme = new Timeline(overmind);

  // develop
  for (int i = 0; i < iter; i++) {
    thyme->develop(overmind);
  }

  List res = thyme->export_as_R_list();

  return res;
}
