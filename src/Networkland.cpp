#include <string.h>

#include "Networkland.h"

Networkland::Networkland(const TStr& pajek_file_path) {
  this->graph = TSnap::LoadPajek<PUNGraph>(pajek_file_path);

  // for (TUNGraph::TNodeI NI = this->graph->BegNI(); NI < this->graph->EndNI(); NI++) {
  //   printf("node id %d with out-degree %d and in-degree %d\n",
  //     NI.GetId(), NI.GetOutDeg(), NI.GetInDeg());
  // }
  
  // for (TUNGraph::TEdgeI EI = this->graph->BegEI(); EI < this->graph->EndEI(); EI++) {
  //   printf("edge (%d, %d)\n", EI.GetSrcNId(), EI.GetDstNId());
  // }
  
  // const TUNGraph::TNodeI huup = this->graph->GetNI(2760);
  // //int fluut = huup.GetNbrNId(0);
  // //printf(std::to_string(fluut).c_str());
  // for (int i = 0; i < huup.GetDeg(); i++) {
  //   printf(std::to_string(huup.GetNbrNId(i)).c_str());
  //   printf("\n");
  // }
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