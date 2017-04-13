#include "Aether.h"

#include "global.h"

Aether::Aether(Networkland* real) {
  this->realworld = real;
}

int Aether::get_ideanumber() {
  return this->mindspace.size();
}

std::vector<int> Aether::get_ideas() {
  std::vector<int> res;
  res.reserve(this->mindspace.size());
  for(auto& idx : this->mindspace) {
    res.push_back(idx->get_identity());
  }
  return res;
}

std::vector< std::vector<vertex_desc> > Aether::get_idea_vertices(){
  std::vector< std::vector <vertex_desc> > res;
  res.reserve(this->mindspace.size());
  for(auto& idx : this->mindspace) {
    res.push_back(idx->get_vertices());
  }
  return res;
}

void Aether::develop() {

  auto& v = this->mindspace;

  if (randunifrange(1, 5) == 1) {
    Idea* newidea = new Idea(realworld);
    v.push_back(newidea);
  }

  // create offset vector
  std::vector<int> offset;
  offset.reserve(v.size());
  for (size_t i=0u; i<v.size(); ++i) {
    offset.push_back(i);
  }
  random_shuffle(
    offset.begin(),
    offset.end(),
    randWrapper
  );

  // iterate over the ideas effectively shuffled by the
  // offset
  for (auto& idx : offset) {
    auto it = v.begin() + idx;
    //infect
    (*it)->infect();
  }


}
