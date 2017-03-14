#ifndef _gluesless_RCPP_POPULATION_H
#define _gluesless_RCPP_POPULATION_H

#include <Rcpp.h>
using namespace Rcpp;

class Population {
public:
  //constructor
  Population(double size_);
  Population(double size_, double birthrate_, double deathrate_);

  // getter
  double size_get();

  // develop functions
  void develop();
  void develop_udef(Function pop_develop_udef);

private:
  // attributes
  double birthrate;
  double deathrate;
  double size;
};

#endif