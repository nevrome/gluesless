#ifndef _gluesless_RCPP_Timeline_H
#define _gluesless_RCPP_Timeline_H

#include <Rcpp.h>
#include <vector>
#include <string>

#include "Aether.h"

using namespace Rcpp;
using namespace std;

class Timeline {

  public:
  Timeline(Aether* start);

  SEXP export_as_R_list();

  void develop(Aether* current);

  private:
  vector<int> ideanumber;
  vector< vector<int> > ideas;
  vector< vector< vector<Vertexdesc> > > idea_vertices;
};

#endif