namespace TSnap {

  inline PUndirNet pajek_file_to_PUndirNet(const TStr& InFNm) {
    PUndirNet Graph = PUndirNet::New();
    TSsParser Ss(InFNm, ssfSpaceSep, true, true, true);
    while ((Ss.Len()==0 || strstr(Ss[0], "*vertices") == NULL) && ! Ss.Eof()) {
      Ss.Next();  Ss.ToLc();
    }
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
          // Edge attributes
          const TInt& value = Ss.GetInt(2);
          Graph->TUndirNet::AddSAttrDatE(Ss.GetInt(0), Ss.GetInt(1), "weight", value);
        }
      }
    }
    return Graph;
  }

  inline PUndirNet get_subgraph_PUndirNet(const PUndirNet& Graph, const TIntV& NIdV) {
  //if (! RenumberNodes) { return TSnap::GetSubGraph(Graph, NIdV); }
    PUndirNet NewGraphPt = TUndirNet::New();
    TUndirNet& NewGraph = *NewGraphPt;
    NewGraph.Reserve(NIdV.Len(), -1);
    TIntSet NIdSet(NIdV.Len());
    for (int n = 0; n < NIdV.Len(); n++) {
      if (Graph->IsNode(NIdV[n])) {
        NIdSet.AddKey(NIdV[n]);
        NewGraph.AddNode(NIdV[n]);
      }
    }
    for (int n = 0; n < NIdSet.Len(); n++) {
      const int SrcNId = NIdSet[n];
      const TUndirNet::TNodeI NI = Graph->GetNI(SrcNId);
      for (int edge = 0; edge < NI.GetOutDeg(); edge++) {
        const int OutNId = NI.GetOutNId(edge);
        if (NIdSet.IsKey(OutNId)) {
          NewGraph.AddEdge(SrcNId, OutNId);
          TInt a;
          Graph->TUndirNet::GetSAttrDatE(SrcNId, OutNId, "weight", a);
          NewGraph.TUndirNet::AddSAttrDatE(SrcNId, OutNId, "weight", a);
        }
      }
    }
    return NewGraphPt;
  }

}