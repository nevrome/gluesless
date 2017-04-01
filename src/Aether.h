#ifndef _gluesless_RCPP_Aether_H
#define _gluesless_RCPP_Aether_H

#include <Rcpp.h>
#include <vector>

#include "Idea.h"

using namespace Rcpp;

class Aether {

  public:
  //constructor
  Aether();

  // getter
  int get_ideanumber();

  // setter
  //

  // developer
  void develop();

  private:
  // attributes
  std::vector<Idea*> mindspace;
};

#endif