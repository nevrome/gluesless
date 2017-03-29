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
void run(SEXP modell_builder){

  // load modell builder
  Rcpp::S4 mb(modell_builder);

  // create idea
  Idea* a = new Idea();
  Idea* b = new Idea();

  Rcout << a->get_identity() << endl;

  // create start environment
  SEXP graphstr = wrap(mb.slot("networkland_env"));
  std::string graphstring = Rcpp::as<std::string>(graphstr);

  Networkland* landofoz = new Networkland(
    graphstring
  );

  // create timeline
  Timeline* thyme = new Timeline(*landofoz);

  // develop
  thyme->develop();

  compare_ideas(a, b);

  return;
}