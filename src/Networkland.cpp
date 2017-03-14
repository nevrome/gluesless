// [[Rcpp::depends(BH)]]

#include <Rcpp.h>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/graph_mutability_traits.hpp>
#include "Networkland.h"

using namespace boost;
using namespace Rcpp;
using namespace std;



// constructor
// Networkland::Networkland() {
//   // create a typedef for the Graph type
//   typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;
//
//   // Make convenient labels for the vertices
//   enum { A, B, C, D, E, N };
//   const int num_vertices = N;
//   const char* name = "ABCDE";
//
//   // writing out the edges in the graph
//   typedef pair<int, int> Edge;
//   Edge edge_array[] =
//     { Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
//       Edge(C,E), Edge(B,D), Edge(D,E) };
//   const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);
//
//   // declare a graph object
//   Graph g(num_vertices);
//
//   // add the edges to the graph object
//   for (int i = 0; i < num_edges; ++i) {
//     add_edge(edge_array[i].first, edge_array[i].second, g);
//   }
//
//   this->env = g;
// }

Networkland::Networkland(std::string graphstring) {

  graph_t graph(0);

  dynamic_properties dp(ignore_other_properties);
  dp.property("node_id", get(&Vertex::name,  graph));
  dp.property("label",   get(&Vertex::label, graph));
  dp.property("shape",   get(&Vertex::shape, graph));
  dp.property("label",   get(&Edge::label,   graph));

  boost::ref_property_map<graph_t *, std::string> gname(get_property(graph, graph_name));
  dp.property("name",    gname);

  std::istringstream is(graphstring);

  read_graphml(is, graph, dp/*, "node_id"*/);
  std::cout << "Graph name: '" << get_property(graph, graph_name) << "'\n";
  get_property(graph, graph_name) = "Let's give it a name";
  write_graphviz_dp(std::cout, graph, dp/*, "node_id"*/);


  //std::istringstream is(graphstring);
  //read_graphml(is, g, dp);
  this->env = graph;
}

// getter
graph_t Networkland::get_graph() {
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
    //.constructor()
    .constructor<std::string>()
    .method("export_graph", &Networkland::export_graph)
    // .method("develop", &Population::develop)
    // .method("develop_udef", &Population::develop_udef)
  ;
}