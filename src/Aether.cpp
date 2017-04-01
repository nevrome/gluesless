#include <Rcpp.h>
#include <vector>

#include "Aether.h"
#include "Idea.h"
#include "global.h"
#include "Networkland.h"

using namespace Rcpp;
using namespace std;

// constructor
Aether::Aether(Networkland* real) {
  this->realworld = real;
}

// getter
int Aether::get_ideanumber() {
  return this->mindspace.size();
}

// developer
void Aether::develop() {

  vector<Idea*> *v = &this->mindspace;

  std::random_shuffle(v->begin(), v->end(), randWrapper);

  if (randunifrange(1, 2) == 1) {
    Idea* newidea = new Idea(realworld);
    v->push_back(newidea);
  }

  for(std::vector<Idea*>::iterator it = v->begin(); it != v->end(); ++it) {
    Rcout << (*it)->get_identity() << endl;
    // (*it)->get_pos();
    (*it)->infect();
  }
}
