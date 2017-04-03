#ifndef _gluesless_RCPP_Aether_H
#define _gluesless_RCPP_Aether_H

#include <Rcpp.h>
#include <vector>
#include <string>

#include "Idea.h"
#include "Networkland.h"

using namespace Rcpp;

class Aether {

  public:
  //constructor
  Aether(Networkland* real);

  // getter
  int get_ideanumber();
  vector<string> get_ideas();
  vector< vector<Vertexdesc> > get_idea_vertices();


  // developer
  void develop();

  private:
  // attributes
  std::vector<Idea*> mindspace;
  Networkland* realworld;
};

#endif