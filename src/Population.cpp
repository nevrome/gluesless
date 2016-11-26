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

// develop function
void Population::develop(Function popdevel) {
  //size = size + size*birthrate - size*deathrate;
  size = as<double>(popdevel(size, birthrate, deathrate));
  return;
}


RCPP_MODULE(Population_module) {
  using namespace Rcpp;

  class_<Population>("Population")
    .constructor<double,double,double>()
    .method("size_get", &Population::size_get)
    .method("develop", &Population::develop)
    ;
}