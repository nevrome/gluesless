#include "Aether.h"

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

int Aether::get_current_graph_size() {
  return(this->realworld->get_number_of_nodes());
}

int Aether::get_number_of_nodes_in_graph() {
  return(this->realworld->get_number_of_nodes());
}
