#include "Idea.h"

Idea::Idea(
  std::string identity,
  Networkland* realworld,
  std::vector<int> start_nodes          
) {
  this->identity = identity;
  this->realworld = realworld;
  this->current_nodes = start_nodes;
}

void Idea::live() {
  printf("hu");
}