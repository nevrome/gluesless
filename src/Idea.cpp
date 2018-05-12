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
  std::vector<int> all_neighbors = this->get_all_neighboring_nodes();
  // remove duplicates from neighbors
  std::vector<int> neighbors_without_doubles = remove_duplicates(all_neighbors);
  // remove the current nodes from neighbors
  std::vector<int> neighbors = erase_elements_of_second_vector_from_the_first(
    neighbors_without_doubles, this->current_nodes
  );
  
  std::vector<std::pair<int, double>> mean_weights_per_neighbor(neighbors.size());
  for (auto& p1 : neighbors) {
    int number_of_edges = 0;
    int weight_per_edge = 0;
    for (auto& p2 : this->current_nodes) {
      if(this->realworld->does_edge_exist(p1, p2)) {
        number_of_edges += 1;
        weight_per_edge += this->realworld->get_edge_weight(p1, p2);
      }
    }
    std::pair<int, double> mean_weight = std::make_pair(
      p1, (double) weight_per_edge / (double) number_of_edges
    ); 
    mean_weights_per_neighbor.push_back(mean_weight);
  }
  
  std::vector<std::pair<int, bool>> success_per_neighbor(neighbors.size());
  for (auto& i : mean_weights_per_neighbor) {
    std::pair<int, bool> success = std::make_pair(
      i.first, i.second > randunifrange(0, 10)
    ); 
    success_per_neighbor.push_back(success);
  }
  
  // delete current nodes from graph
  for (auto& i : this->current_nodes) {
    if(this->realworld->does_node_exist(i)) {
      this->realworld->delete_nodes(i);
      this->dead_nodes.push_back(i);
    }
  }
  
  // forget current nodes and make neighbors new current nodes
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