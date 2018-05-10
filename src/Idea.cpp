#include "Idea.h"

Idea::Idea(
  std::string identity,
  Networkland* realworld,
  std::vector<int> start_nodes ){         
//): current_nodes(1000), dead_nodes(100000) {
  this->identity = identity;
  this->realworld = realworld;
  this->current_nodes = start_nodes;
}

void Idea::live() {
  this->expand();
}

void Idea::expand() {
  auto cn = this->current_nodes;
  this->dead_nodes.insert(this->dead_nodes.end(), cn.begin(), cn.end());
  this->current_nodes.clear();
  for (auto& i : cn) {
    // printf("hu");
    std::vector<int> neighbors = this->realworld->get_neighboring_nodes(i);
    this->current_nodes.insert(this->current_nodes.end(), neighbors.begin(), neighbors.end());
  }
}

std::vector<int> Idea::get_nodes() {
  auto& dn = this->dead_nodes;
  auto& cn = this->current_nodes;
  dn.insert(dn.end(), cn.begin(), cn.end());
  return(dn);
}