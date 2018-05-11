#include <string.h>

#include "Networkland.h"

Networkland::Networkland(const TStr& pajek_file_path) {
  this->graph = TSnap::LoadPajek<PUNGraph>(pajek_file_path);

}

Networkland::Networkland(PUNGraph newgraph) {
  this->graph = newgraph;
}

std::vector<int> Networkland::get_neighboring_nodes(int node) {
  const TUNGraph::TNodeI nodei = this->graph->GetNI(node);
  int amount_of_neighbors = nodei.GetDeg();
  std::vector<int> neighboring_nodes;
  neighboring_nodes.reserve(amount_of_neighbors);
  for (int i = 0; i < amount_of_neighbors; i++) {
    neighboring_nodes.push_back(nodei.GetNbrNId(i));
    //printf(std::to_string(nodei.GetNbrNId(i)).c_str());
  }
  return(neighboring_nodes);
}

int Networkland::get_number_of_nodes() {
  this->graph->GetNodes();
}

void Networkland::delete_nodes(int node) {
  this->graph->DelNode(node);
}

bool Networkland::does_node_exist(int node) {
  this->graph->IsNode(node);
}

