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
