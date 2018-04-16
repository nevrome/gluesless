#include <string.h>

#include "Networkland.h"

Networkland::Networkland(const TStr& pajek_file_path) {
    this->graph = TSnap::LoadPajek<PUNGraph>(pajek_file_path);

    for (TUNGraph::TNodeI NI = this->graph->BegNI(); NI < this->graph->EndNI(); NI++) {
      printf("node id %d with out-degree %d and in-degree %d\n",
        NI.GetId(), NI.GetOutDeg(), NI.GetInDeg());
    }
    
    // for (TUNGraph::TEdgeI EI = this->graph->BegEI(); EI < this->graph->EndEI(); EI++) {
    //   printf("edge (%d, %d)\n", EI.GetSrcNId(), EI.GetDstNId());
    // }
    
    const TUNGraph::TNodeI huup = this->graph->GetNI(2760);
    int fluut = huup.GetNbrNId(0);
    printf(std::to_string(fluut).c_str());
}

Networkland::Networkland(PUNGraph newgraph) {
  this->graph = newgraph;
}