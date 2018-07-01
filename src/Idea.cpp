#include <algorithm>
#include <tuple>
#include <cmath>

#include "Idea.h"
#include "global_vector_operations.h"
#include "global_snap_modifications.h"

Idea::Idea(
  std::string identity,
  Networkland* realworld,
  std::vector<int> start_nodes
){
  this->current_nodes.reserve(1000);
  this->dead_nodes.reserve(100000);

  this->identity = identity;
  this->realworld = realworld;
  this->current_nodes = start_nodes;
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
  
  // make decision, which neighbors can be converted
  std::vector<int> converted = this->select_nodes_to_convert(neighbors);
  
  // delete current nodes from graph
  for (auto& i : this->current_nodes) {
    if(this->realworld->does_node_exist(i)) {
      this->realworld->delete_nodes(i);
      this->dead_nodes.push_back(i);
    }
  }
  
  // forget current nodes and make neighbors new current nodes
  this->current_nodes.clear();
  this->current_nodes.insert(this->current_nodes.end(), converted.begin(), converted.end());
  
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

std::vector<int> Idea::select_nodes_to_convert(std::vector<int> neighbors) {
  
  TIntV all_nodes_involved = combine_vectors_to_TIntV(neighbors, this->current_nodes);
  PUndirNet small_subgraph = TSnap::get_subgraph_PUndirNet(this->realworld->get_graph(), all_nodes_involved);
  
  // calculate number and mean weight per neighbor
  std::vector<std::tuple<int, double, int>> max_weights_and_contacts_per_neighbor(neighbors.size());
  for (auto& p1 : neighbors) {
    int number_of_edges = 0;
    int max_weight = 0;
    for (auto& p2 : this->current_nodes) {
      if(small_subgraph->IsEdge(p1, p2)) {
        number_of_edges += 1;
        // weight_per_edge += this->realworld->get_edge_weight(p1, p2);
        TInt a;
        small_subgraph->GetSAttrDatE(p1, p2, "weight", a);
        //weight_per_edge += (int) a;
        if ( (double) a > max_weight) {
          max_weight = (double) a;
        }
      }
    }
    std::tuple<int, double, int> max_weight_and_contacts = std::make_tuple(
      p1, max_weight, number_of_edges
    );
    max_weights_and_contacts_per_neighbor.push_back(max_weight_and_contacts);
  }
  
  // make random decision to convert or ignore a node based on the edge weight
  std::vector<std::pair<int, bool>> success_per_neighbor(neighbors.size());
  for (auto& i : max_weights_and_contacts_per_neighbor) {
    // make decision. If more than one contact, then there's a convincing bonus
    std::pair<int, bool> success = std::make_pair(
      std::get<0>(i), std::get<1>(i) * log2( (double) std::get<2>(i) + 1) >= randunifrange(0, 100)
    ); 
    success_per_neighbor.push_back(success);
  }
  
  // collect converted nodes into a result vector
  std::vector<int> converted;
  converted.reserve(neighbors.size());
  for (auto& i : success_per_neighbor) {
    if (i.second) {
      converted.push_back(i.first);
    }
  }
  
  return(converted);
  
}
  
std::vector<int> Idea::get_nodes() {
  
  auto& dn = this->dead_nodes;
  auto& cn = this->current_nodes;
  dn.insert(dn.end(), cn.begin(), cn.end());
  
  return(dn);
  
}

std::string Idea::get_identity() {
  return(this->identity);
}
