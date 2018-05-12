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
