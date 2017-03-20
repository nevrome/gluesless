#include <Rcpp.h>
#include <vector>

#include "Timeline.h"
#include "Networkland.h"

using namespace Rcpp;
using namespace std;

// constructor
Timeline::Timeline(Networkland startland) {
  this->spacetime.push_back(startland);
}

// getter
vector<Networkland> Timeline::get_spacetime() {
  return spacetime;
}

// setter
void Timeline::set_spacetime(vector<Networkland> newspace) {
  spacetime = newspace;
}

// developer
void Timeline::develop() {
  spacetime.push_back(
    spacetime.back().develop()
  );
}
