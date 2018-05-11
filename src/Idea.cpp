#include <algorithm>

#include "Idea.h"

Idea::Idea(
  std::string identity,
  Networkland* realworld,
  std::vector<int> start_nodes
){
  this->identity = identity;
  this->realworld = realworld;
  this->current_nodes = start_nodes;
  
  this->current_nodes.reserve(1000);
  this->dead_nodes.reserve(100000);
}

void Idea::live() {
  this->expand();
}

void Idea::expand() {
  // get all neighboring nodes
  std::vector<int> neighbors;
  neighbors.reserve(1000);
  for (auto& i : this->current_nodes) {
    if(this->realworld->does_node_exist(i)) {
      std::vector<int> new_neighbors = this->realworld->get_neighboring_nodes(i);
      neighbors.insert(neighbors.end(), new_neighbors.begin(), new_neighbors.end());
    }
  }
  // remove duplicates from neighbors
  std::sort(neighbors.begin(), neighbors.end());
  std::vector<int>::iterator it;
  it = std::unique(neighbors.begin(), neighbors.end());  // 10 20 30 20 10 ?  ?  ?  ?
  neighbors.resize(std::distance(neighbors.begin(), it)); // 10 20 30 20 10
  // remove the current nodes from neighbors
  neighbors.erase(
    remove_if(
      neighbors.begin(), neighbors.end(),
      [&](auto x){ return find(this->current_nodes.begin(), this->current_nodes.end() , x) != this->current_nodes.end(); }
    ),
    neighbors.end()
  );
  // delete current nodes
  for (auto& i : this->current_nodes) {
    if(this->realworld->does_node_exist(i)) {
      this->realworld->delete_nodes(i);
      this->dead_nodes.push_back(i);
    }
  }
  // make neighbors current nodes
  this->current_nodes.clear();
  this->current_nodes.insert(this->current_nodes.end(), neighbors.begin(), neighbors.end());
}
  
std::vector<int> Idea::get_nodes() {
  auto& dn = this->dead_nodes;
  auto& cn = this->current_nodes;
  dn.insert(dn.end(), cn.begin(), cn.end());
  return(dn);
}