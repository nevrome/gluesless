#ifndef _gluesless_RCPP_Timeline_H
#define _gluesless_RCPP_Timeline_H

#include <Rcpp.h>
#include <vector>

#include "Networkland.h"

using namespace Rcpp;

class Timeline {

  public:
  //constructor
  Timeline(Networkland startland);

  // getter
  // double size_get();

  // develop functions
  // void develop();

  private:
  // attributes
  vector<Networkland> spacetime;
};

#endif