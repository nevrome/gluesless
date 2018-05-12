#include <algorithm>

#include "Idea.h"
#include "global_vector_operations.h"

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
  std::vector<int> all_neighbors;
  all_neighbors.reserve(1000);
  all_neighbors = this->get_all_neighboring_nodes();
  // remove duplicates from neighbors
  std::vector<int> neighbors_without_doubles;
  neighbors_without_doubles.reserve(1000);
  neighbors_without_doubles = remove_duplicates(all_neighbors);
  // remove the current nodes from neighbors
  std::vector<int> neighbors;
  neighbors.reserve(1000);
  neighbors = erase_elements_of_second_vector_from_the_first(
    neighbors_without_doubles, this->current_nodes
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

std::vector<int> Idea::get_all_neighboring_nodes() {
  std::vector<int> neighbors;
  neighbors.reserve(1000);
  for (auto& i : this->current_nodes) {
    if(this->realworld->does_node_exist(i)) {
      std::vector<int> new_neighbors = this->realworld->get_neighboring_nodes(i);
      neighbors.insert(neighbors.end(), new_neighbors.begin(), new_neighbors.end());
    }
  }
  return(neighbors);
}
  
std::vector<int> Idea::get_nodes() {
  auto& dn = this->dead_nodes;
  auto& cn = this->current_nodes;
  dn.insert(dn.end(), cn.begin(), cn.end());
  return(dn);
}