#ifndef _gluesless_RCPP_Idea_H
#define _gluesless_RCPP_Idea_H

#include <Rcpp.h>
#include <string>

using namespace Rcpp;
using namespace std;

class Idea {

  public:
  //constructor
  Idea();

  // getter
  string get_identity();

  // develop functions
  // mutate();
  // conjugate();
  // infect();

  private:
  // attributes
  string identity;

};

#endif