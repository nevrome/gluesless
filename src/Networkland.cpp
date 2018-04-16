#include "Networkland.h"

Networkland::Networkland(const TStr& pajek_file_path) {
    this->graph = TSnap::LoadPajek<PUNGraph>(pajek_file_path);
    
    for (TUNGraph::TEdgeI EI = this->graph->BegEI(); EI < this->graph->EndEI(); EI++) {
      printf("edge (%d, %d)\n", EI.GetSrcNId(), EI.GetDstNId());
    }
}

Networkland::Networkland(PUNGraph newgraph) {
  this->graph = newgraph;
}