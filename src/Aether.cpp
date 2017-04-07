#include <Rcpp.h>
#include <vector>
#include <string>

#include "Aether.h"
#include "Idea.h"
#include "global.h"
#include "Networkland.h"

using namespace Rcpp;
using namespace std;

Aether::Aether(Networkland* real) {
  this->realworld = real;
}

int Aether::get_ideanumber() {
  return this->mindspace.size();
}

vector<int> Aether::get_ideas() {
  vector<int> res;
  vector<Idea*> *v = &this->mindspace;
  for(std::vector<Idea*>::iterator it = v->begin(); it != v->end(); ++it) {
    res.push_back((*it)->get_identity());
  }
  return res;
}

vector< vector<Vertexdesc> > Aether::get_idea_vertices(){
  vector< vector <Vertexdesc> > res;
  vector<Idea*> *v = &this->mindspace;
  for(std::vector<Idea*>::iterator it = v->begin(); it != v->end(); ++it) {
    res.push_back((*it)->get_vertices());
  }
  return res;
}

void Aether::develop() {

  vector<Idea*> *v = &this->mindspace;

  if (randunifrange(1, 5) == 1) {
    Idea* newidea = new Idea(realworld);
    v->push_back(newidea);
  }

  // create offset vector
  vector<int> offset;
  for (int i=0; i<v->size(); ++i) {
    offset.push_back(i);
  }
  random_shuffle(
    offset.begin(),
    offset.end(),
    randWrapper
  );

  // iterate over the ideas effectively shuffled by the offset
  vector<Idea*>::iterator dummy_iter;
  for (vector<int>::iterator it=offset.begin(); it!=offset.end(); ++it) {
    dummy_iter = v->begin() + *it;
    //infect
    (*dummy_iter)->infect();
  }


}
