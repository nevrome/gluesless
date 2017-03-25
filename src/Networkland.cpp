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
}

// getter
graph_t Networkland::get_graph() {
  return env;
}

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

// developer
Networkland Networkland::develop() {

  // copy Networkland object to prepare a successor in the timeline
  Networkland newland = *this;

  // extract graph from Networkland
  graph_t g = newland.get_graph();

  // define vertex iterator object
  typedef graph_traits<graph_t>::vertex_iterator vertex_iter;

  // create a pair to store the vertex iterators
  std::pair<vertex_iter, vertex_iter> vp;

  vp = vertices(g);

  // iterate over all vertices
  for (vp; vp.first != vp.second; ++vp.first) {

    Rcout << g[*vp.first].name << " " << g[*vp.first].gender << std::endl;
  }
  Rcout << std::endl;

  return newland;
}