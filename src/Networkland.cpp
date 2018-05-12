#include <string.h>

#include "Networkland.h"
#include <iostream>

#include "global_load_pajek.h"

Networkland::Networkland(const TStr& pajek_file_path) {
  this->graph = TSnap::pajek_file_to_PUndirNet(pajek_file_path);
  printf("Input graph successfully loaded.");
  printf("\n");
}

Networkland::Networkland(PUndirNet newgraph) {
  this->graph = newgraph;
}

std::vector<int> Networkland::get_neighboring_nodes(int node) {
  const TUndirNet::TNodeI nodei = this->graph->GetNI(node);
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

bool Networkland::does_edge_exist(int first_node, int second_node) {
  this->graph->IsEdge(first_node, second_node);
}

int Networkland::get_edge_weight(int first_node, int second_node) {
  TInt a;
  this->graph->GetSAttrDatE(first_node, second_node, "weight", a);
  return((int) a);
}

PUndirNet Networkland::get_graph() {
  return(this->graph);
}
