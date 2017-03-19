#include <Rcpp.h>
using namespace Rcpp;
#include "Idea.h"

// constructor
Idea::Idea() {
}


// RCPP_Module definition
RCPP_MODULE(Idea_module) {
  using namespace Rcpp;

  class_<Idea>("Idea")
    .constructor()
    ;
}