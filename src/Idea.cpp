#include <Rcpp.h>
#include <string>

#include "Idea.h"
#include "global.h"

using namespace Rcpp;
using namespace std;

// constructor
Idea::Idea() {
  this->identity = random_string(30);
}

// getter
string Idea::get_identity() {
  return identity;
}

