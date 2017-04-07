#include <Rcpp.h>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/graph_mutability_traits.hpp>
#include <boost/range/iterator_range.hpp>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector

#include "Networkland.h"
#include "global.h"

using namespace boost;
using namespace Rcpp;
using namespace std;

// constructor
Networkland::Networkland(std::string graphstring) {

  graph_t graph(0);

  dynamic_properties dp(ignore_other_properties);
  dp.property("id",       get(&Vertex::id,     graph));
  dp.property("x",        get(&Vertex::x,      graph));
  dp.property("y",        get(&Vertex::y,      graph));
  dp.property("distance", get(&Edge::distance, graph));

  boost::ref_property_map<graph_t *, std::string> gname(get_property(graph, graph_name));
  dp.property("graph_name", gname);

  std::istringstream is(graphstring);

  read_graphml(is, graph, dp);

  this->env = graph;
}

Networkland::Networkland(graph_t newenv) {
  this->env = newenv;
}

// getter
graph_t Networkland::get_graph() {
  return env;
}

int Networkland::get_number_of_vertices() {
  return num_vertices(env);
}

vector<Vertexdesc> Networkland::get_adjacent_vertices(Vertexdesc v) {
  vector<Vertexdesc> res;
  IndexMap index = get(vertex_index, env);
  typename graph_traits<graph_t>::adjacency_iterator ai;
  typename graph_traits<graph_t>::adjacency_iterator ai_end;
  for (tie(ai, ai_end) = adjacent_vertices(v, env); ai != ai_end; ++ai) {
    res.push_back(index[*ai]);
  }
  return res;
}

double Networkland::get_distance_between_two_vertices(Vertexdesc a, Vertexdesc b) {

  // create a pair to store the edge iterators
  pair<Edgedesc, bool> edgepair;

  edgepair = edge(a, b, env);

  Rcout << "Diff between: " << a << " and " << b << " is " << env[edgepair.first].distance << endl;
  return env[edgepair.first].distance;
}

// R-exporter
// std::string Networkland::export_graph() {
//
//   graph_t graph = this->get_graph();
//
//   dynamic_properties dp(ignore_other_properties);
//   dp.property("name", get(&Vertex::name,  graph));
//   dp.property("age",   get(&Vertex::age, graph));
//   dp.property("gender",   get(&Vertex::gender, graph));
//   dp.property("friendship",   get(&Edge::friendship,   graph));
//   dp.property("advice",   get(&Edge::advice,   graph));
//
//   ostringstream fout;
//   write_graphml(fout,
//                 this->get_graph(),
//                 dp,
//                 false);
//   string test = fout.str();
//
//   return test;
// }