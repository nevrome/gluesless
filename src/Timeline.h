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
  //constructor
  Timeline(Aether* start);

  // getter
  //vector<Networkland> get_spacetime();

  // setter
  //void set_spacetime(vector<Networkland> newspace);

  // R-exporter
  SEXP export_as_R_list();

  // developer
  void develop(Aether* current);

  private:
  // attributes
  vector<int> ideanumber;
  vector< vector<string> > ideas;
  vector< vector< vector<Vertexdesc> > > idea_vertices;
};

#endif