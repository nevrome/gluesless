#include "Aether.h"
#include "global_general.h"

Aether::Aether(Networkland* real) {
  this->realworld = real;
}

void Aether::develop() {
  
  // let every idea act in random order
  auto& v = this->mindspace;
  std::shuffle(v.begin(), v.end(), rng);
  for (auto& current_idea : v) {
    current_idea->live();
  }
  
}

void Aether::add_idea_to_mindspace(Idea* new_idea) {
  this->mindspace.push_back(new_idea);
}
