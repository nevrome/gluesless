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

SEXP Timeline::export_as_R_list() {
  List res;

  NumericVector ideanumber_nv(ideanumber.begin(), ideanumber.end());

  List ideas_list;
  for (vector< vector<string> >::iterator it=ideas.begin(); it!=ideas.end(); ++it) {
    StringVector idea_nv((*it).begin(), (*it).end());
    ideas_list.push_back(idea_nv);
  }


  res["number_of_ideas"] = ideanumber_nv;
  res["ideas"] = ideas_list;


  return res;
}

// developer
void Timeline::develop(Aether* current) {
  current->develop();

  this->ideanumber.push_back(current->get_ideanumber());
  this->ideas.push_back(current->get_ideas());
}
