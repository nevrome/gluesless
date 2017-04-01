#include <Rcpp.h>
#include <vector>

#include "Timeline.h"
#include "Aether.h"

using namespace Rcpp;
using namespace std;

// constructor
Timeline::Timeline(Aether* start) {
  this->ideanumber.push_back(start->get_ideanumber());
}

// getter
// vector<Networkland> Timeline::get_spacetime() {
//   return spacetime;
// }

// setter
// void Timeline::set_spacetime(vector<Networkland> newspace) {
//   spacetime = newspace;
// }

// developer
void Timeline::develop(Aether* current) {
  current->develop();
  this->ideanumber.push_back(current->get_ideanumber());
}
