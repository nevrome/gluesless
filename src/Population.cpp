#include <Rcpp.h>
using namespace Rcpp;
#include "Population.h"



// constructor
Population::Population(double size_, double birthrate_, double deathrate_) {
  this->size = size_;
  this->birthrate = birthrate_;
  this->deathrate = deathrate_;
}

// getter
double Population::size_get() {
  return size;
}

// develop functions
void Population::develop() {
  size = size + size*birthrate - size*deathrate;
  return;
}

void Population::develop_udef(Function pop_develop_udef) {
  size = as<double>(pop_develop_udef(size, birthrate, deathrate));
  return;
}

// RCPP_Module definition
RCPP_MODULE(Population_module) {
  using namespace Rcpp;

  class_<Population>("Population")
    .constructor<double,double,double>()
    .method("size_get", &Population::size_get)
    .method("develop", &Population::develop)
    .method("develop_udef", &Population::develop_udef)
    ;
}