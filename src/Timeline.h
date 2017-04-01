#ifndef _gluesless_RCPP_Timeline_H
#define _gluesless_RCPP_Timeline_H

#include <Rcpp.h>
#include <vector>

#include "Aether.h"

using namespace Rcpp;

class Timeline {

  public:
  //constructor
  Timeline(Aether* start);

  // getter
  //vector<Networkland> get_spacetime();

  // setter
  //void set_spacetime(vector<Networkland> newspace);

  // developer
  void develop(Aether* current);

  private:
  // attributes
  std::vector<int> ideanumber;
};

#endif