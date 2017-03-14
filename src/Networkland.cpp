// [[Rcpp::depends(BH)]]

#include <Rcpp.h>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include "Networkland.h"

using namespace boost;
using namespace Rcpp;
using namespace std;



// constructor
Networkland::Networkland() {
  // create a typedef for the Graph type
  typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;

  // Make convenient labels for the vertices
  enum { A, B, C, D, E, N };
  const int num_vertices = N;
  const char* name = "ABCDE";

  // writing out the edges in the graph
  typedef pair<int, int> Edge;
  Edge edge_array[] =
    { Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
      Edge(C,E), Edge(B,D), Edge(D,E) };
  const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);

  // declare a graph object
  Graph g(num_vertices);

  // add the edges to the graph object
  for (int i = 0; i < num_edges; ++i) {
    add_edge(edge_array[i].first, edge_array[i].second, g);
  }

  this->env = g;
}

// getter
Graph Networkland::get_graph() {
  return env;
}

// R-exporter
std::string Networkland::export_graph() {
  dynamic_properties dp;

  ostringstream fout;
  write_graphml(fout,this->get_graph(),dp,false);
  string test = fout.str();

  return test;
}

// develop functions
// void Population::develop() {
//   size = size + size*birthrate - size*deathrate;
//   return;
// }

// void Population::develop_udef(Function pop_develop_udef) {
//   size = as<double>(pop_develop_udef(size, birthrate, deathrate));
//   return;
// }

// RCPP_Module definition
RCPP_MODULE(Networkland_module) {
  using namespace Rcpp;

  class_<Networkland>("Networkland")
    .constructor()
    .method("export_graph", &Networkland::export_graph)
    // .method("develop", &Population::develop)
    // .method("develop_udef", &Population::develop_udef)
  ;
}