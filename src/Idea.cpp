#include "Idea.h"

Idea::Idea(
  std::string identity,
  Networkland* realworld,
  std::vector<int> start_nodes          
): current_nodes(1000), dead_nodes(100000) {
  this->identity = identity;
  this->realworld = realworld;
  this->current_nodes = start_nodes;
}

void Idea::live() {
  this->expand();
}

void Idea::expand() {
  auto& cv = this->current_nodes;
  this->current_nodes.clear();
  this->dead_nodes.insert(this->dead_nodes.end(), cv.begin(), cv.end());
  for (auto& i : cv) {
    std::vector<int> neighbors = this->realworld->get_neighboring_nodes(i);
    this->current_nodes.insert(this->current_nodes.end(), neighbors.begin(), neighbors.end());
  }
}