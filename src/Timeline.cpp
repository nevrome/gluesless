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


// // RCPP_Module definition
// RCPP_MODULE(Timeline_module) {
//   using namespace Rcpp;
//
//   class_<Timeline>("Timeline")
//     .constructor<Networkland>();
//     ;
// }