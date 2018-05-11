#pragma once

#include "Snap.h"
#include "vector"
#include <network.h>

//! Real world represented with a network - ABM environment
/*!
 Could represent a spatial, cultural etc. network.
 */

class Networkland {
    
  public:
  Networkland(const TStr& pajek_file_path);
  Networkland(PUndirNet newgraph);

  std::vector<int> get_neighboring_nodes(int node);
  void delete_nodes(int node);
  int get_number_of_nodes();
  bool does_node_exist(int node);


  private:
  PUndirNet graph;
};

namespace TSnap {

template <class PGraph> PGraph LoadPajek(const TStr& InFNm);

template <class PGraph>

PUndirNet LoadPajek_better(const TStr& InFNm) {
  PGraph Graph = PGraph::TObj::New();
  TSsParser Ss(InFNm, ssfSpaceSep, true, true, true);
  while ((Ss.Len()==0 || strstr(Ss[0], "*vertices") == NULL) && ! Ss.Eof()) {
    Ss.Next();  Ss.ToLc(); }
  // nodes
  bool EdgeList = true;
  EAssert(strstr(Ss[0], "*vertices") != NULL);
  while (Ss.Next()) {
    Ss.ToLc();
    if (Ss.Len()>0 && Ss[0][0] == '%') { continue; } // comment
    if (strstr(Ss[0], "*arcslist")!=NULL || strstr(Ss[0],"*edgeslist")!=NULL) { EdgeList=false; break; } 
    if (strstr(Ss[0], "*arcs")!=NULL || strstr(Ss[0],"*edges")!=NULL) { break; } // arcs are directed, edges are undirected
    Graph->AddNode(Ss.GetInt(0));
  }
  // edges
  while (Ss.Next()) {
    if (Ss.Len()>0 && Ss[0][0] == '%') { continue; } // comment
    if (Ss.Len()>0 && Ss[0][0] == '*') { break; }
    if (EdgeList) {
      // <source> <destination> [ <weight> ]
      if (Ss.Len() >= 2 && Ss.IsInt(0) && Ss.IsInt(1) && (const TInt&)Ss.IsInt(2)) {
        Graph->AddEdge(Ss.GetInt(0), Ss.GetInt(1));
        const TInt& value = Ss.GetInt(2);
        //printf(std::to_string(value).c_str());
        Graph->TUndirNet::AddSAttrDatE(Ss.GetInt(0), Ss.GetInt(1), "weight", value);
      }
    } else {
      // <source> <destination1> <destination2> <destination3> ...
      const int SrcNId = Ss.GetInt(0);
      for (int i = 1; i < Ss.Len(); i++) {
        Graph->AddEdge(SrcNId, Ss.GetInt(i)); }
    }
  }
  return Graph;
}

}
