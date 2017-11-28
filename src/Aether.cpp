#include <math.h>

#include "Aether.h"
#include "global.h"

Aether::Aether(Networkland* real) {
  this->realworld = real;
}

void Aether::add_idea_to_mindspace(Idea* new_idea) {
  this->mindspace.push_back(new_idea);
}

std::vector<std::string> Aether::get_ideas() {
  std::vector<std::string> res;
  res.reserve(this->mindspace.size());
  for (auto& idx : this->mindspace) {
    res.push_back(idx->get_identity());
  }
  return res;
}

std::vector< std::map<vertex_desc, double> > Aether::get_idea_expansions(){
  std::vector< std::map<vertex_desc, double> > res;
  res.reserve(this->mindspace.size());
  for (auto& idx : this->mindspace) {
    res.push_back(idx->get_expansion());
  }
  return res;
}

void Aether::develop() {

  // create convenient short
  auto& v = this->mindspace;

  for (auto& idx : v) {
    idx->live();
  }


}
