#include <Rcpp.h>

#include "Idea.h"

using namespace Rcpp;

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