#include <Rcpp.h>
using namespace Rcpp;
#include "Timeline.h"

// constructor
Timeline::Timeline() {
}


// RCPP_Module definition
RCPP_MODULE(Timeline_module) {
  using namespace Rcpp;

  class_<Timeline>("Timeline")
    .constructor()
    ;
}