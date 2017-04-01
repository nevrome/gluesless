#include <Rcpp.h>
#include <vector>

#include "Aether.h"
#include "Idea.h"
#include "global.h"

using namespace Rcpp;
using namespace std;

// constructor
Aether::Aether() {
}

// getter
int Aether::get_ideanumber() {
  return this->mindspace.size();
}

// setter
// void Aether::set_spacetime(vector<Networkland> newspace) {
//   spacetime = newspace;
// }

// developer
void Aether::develop() {
  vector<Idea*> *v = &this->mindspace;

  if (randunifrange(1, 2) == 1) {
    Idea* newidea = new Idea();
    v->push_back(newidea);
  }

  for(std::vector<Idea*>::iterator it = v->begin(); it != v->end(); ++it) {
    Rcout << (*it)->get_identity() << endl;
  }
}
