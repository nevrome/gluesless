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
  vector<Networkland> get_spacetime();

  // setter
  void set_spacetime(vector<Networkland> newspace);

  // developer
  void develop();

  private:
  // attributes
  vector<Networkland> spacetime;
};

#endif