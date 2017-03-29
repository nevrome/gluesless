#ifndef _gluesless_RCPP_Idea_H
#define _gluesless_RCPP_Idea_H

#include <Rcpp.h>
#include <string>

#include "Idea.h"

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

std::string create_random_string(size_t length);
size_t compare_strings(const std::string &s1, const std::string &s2);
size_t compare_ideas(Idea* a, Idea* b);

#endif