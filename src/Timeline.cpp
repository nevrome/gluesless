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
  this->ideas.push_back(current->get_ideas());
  this->idea_vertices.push_back(current->get_idea_vertices());
}

// R-exporter
SEXP Timeline::export_as_R_list() {
  List res;

  NumericVector ideanumber_nv(ideanumber.begin(), ideanumber.end());

  List ideas_list;

  List identity;
  for (vector< vector<string> >::iterator it=ideas.begin(); it!=ideas.end(); ++it) {
    StringVector idea_sv((*it).begin(), (*it).end());
    identity.push_back(idea_sv);
  }
  ideas_list["identity"] = identity;

  List vertices;
  for (vector< vector< vector<Vertexdesc> > >::iterator it1=idea_vertices.begin();
      it1!=idea_vertices.end(); ++it1) {
    List test;
    for (vector< vector<Vertexdesc> >::iterator it2=(*it1).begin();
        it2!=(*it1).end(); ++it2) {
      NumericVector vert_nv((*it2).begin(), (*it2).end());
      test.push_back(vert_nv);
    }
    vertices.push_back(test);
  }
  ideas_list["vertices"] = vertices;

  res["number_of_ideas"] = ideanumber_nv;
  res["idea_timesteps"] = ideas_list;

  return res;
}