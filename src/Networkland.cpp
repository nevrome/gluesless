#include <Rcpp.h>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/graph_mutability_traits.hpp>

#include "Networkland.h"
#include "Idea.h"

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
  dp.property("name", get(&Vertex::name,  graph));
  dp.property("age",   get(&Vertex::age, graph));
  dp.property("gender",   get(&Vertex::gender, graph));
  dp.property("friendship",   get(&Edge::friendship,   graph));
  dp.property("advice",   get(&Edge::advice,   graph));

  boost::ref_property_map<graph_t *, std::string> gname(get_property(graph, graph_name));
  dp.property("name",    gname);

  std::istringstream is(graphstring);

  read_graphml(is, graph, dp/*, "node_id"*/);
  Rcout << "Graph name: '" << get_property(graph, graph_name) << "'\n";

  this->env = graph;
  //this->prop = dp;
}

// getter
graph_t Networkland::get_graph() {
  return env;
}

//dynamic_properties Networkland::get_graph_properties() {
//  return prop;
//}

// R-exporter
std::string Networkland::export_graph() {

  graph_t graph = this->get_graph();

  dynamic_properties dp(ignore_other_properties);
  dp.property("name", get(&Vertex::name,  graph));
  dp.property("age",   get(&Vertex::age, graph));
  dp.property("gender",   get(&Vertex::gender, graph));
  dp.property("friendship",   get(&Edge::friendship,   graph));
  dp.property("advice",   get(&Edge::advice,   graph));

  ostringstream fout;
  write_graphml(fout,
                this->get_graph(),
                dp,
                false);
  string test = fout.str();

  return test;
}
