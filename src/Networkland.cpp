#include "Networkland.h"

#include <algorithm>
#include <vector>

#include <boost/graph/graph_mutability_traits.hpp>
#include <boost/range/iterator_range.hpp>

#include "Idea.h"
#include "global.h"

using namespace boost;

// define dummy in- and output definitions for Idea vectors - boost needs that, I don't...
// https://stackoverflow.com/questions/40685196/read-boost-graph-boostread-graphviz-where-vertex-contains-vector
// https://stackoverflow.com/questions/32279268/using-two-objects-as-hash-key-for-an-unordered-map-or-alternatives/32281365#32281365
static inline std::ostream& operator<<(std::ostream& os, std::vector<Idea*> const& i) {
  // here I would have to do something, if this feature would be necessary
  return os;
}
static inline std::istream& operator>>(std::istream& is, std::vector<Idea*> const& i) {
  // here I would have to do something, if this feature would be necessary
  return is;
}

Networkland::Networkland(const std::string& graphstring) {

  // create empty graph object
  graph_t graph(0);

  // add graph properties
  dynamic_properties dp(ignore_other_properties);
  dp.property("id",                 get(&Vertex::id,                graph));
  dp.property("x",                  get(&Vertex::x,                 graph));
  dp.property("y",                  get(&Vertex::y,                 graph));
  dp.property("ioi",                get(&Vertex::ioi,               graph));
  dp.property("distance",           get(&Edge::distance,            graph));

  ref_property_map<graph_t *, std::string> gname(
      get_property(graph, graph_name)
    );
  dp.property("graph_name", gname);

  std::istringstream is(graphstring);

  // read graph from string
  read_graphml(is, graph, dp);

  // add properties to graph that are not part of the input
  dp.property("present_ideas",      get(&Vertex::present_ideas,     graph));

  this->env = graph;
}

Networkland::Networkland(graph_t newenv) {
  this->env = newenv;
}

graph_t Networkland::get_graph() { return env; }
int Networkland::get_number_of_vertices() { return num_vertices(env); }

std::vector<vertex_desc> Networkland::get_adjacent_vertices(vertex_desc v) {
  std::vector<vertex_desc> res;
  res.reserve(10);
  index_map index = get(vertex_index, env);
  typename graph_trs::adjacency_iterator ai;
  typename graph_trs::adjacency_iterator ai_end;
  for (tie(ai, ai_end) = adjacent_vertices(v, env); ai != ai_end; ++ai) {
    res.push_back(index[*ai]);
  }
  return res;
}

double Networkland::get_distance_between_two_vertices(
    const vertex_desc& a, const vertex_desc& b
  ) {
  // create a pair to store the edge iterators
  std::pair<edge_desc, bool> edgepair;
  edgepair = edge(a, b, env);
  return env[edgepair.first].distance;
}

bool Networkland::are_adjacent(
    const vertex_desc& a, const vertex_desc& b
  ) {
  return edge(a, b, env).second;
}

double Networkland::get_vertex_ioi(const vertex_desc& a) {
  return env[a].ioi;
}

void Networkland::set_vertex_ioi(const vertex_desc& a, double new_ioi) {
  env[a].ioi = new_ioi;
}

size_t Networkland::get_num_ideas(const vertex_desc& a) {
  return env[a].present_ideas.size();
}

Idea* Networkland::get_weakest_idea(const vertex_desc& a) {
  std::vector<Idea*> idea_vec = env[a].present_ideas;
  Idea* weakest;
  bool first = true;
  int weakest_power = 0;
  for(auto& p1 : idea_vec) {
    if (first || p1->get_power() < weakest_power) {
      weakest = p1;
      weakest_power = p1->get_power();
      first = false;
    }
  }
  return weakest;
}

void Networkland::push_idea(const vertex_desc& a, Idea* i) {
  env[a].present_ideas.push_back(i);
}

void Networkland::erase_idea(const vertex_desc& a, Idea* i) {
  env[a].present_ideas.erase(
    std::remove(
      env[a].present_ideas.begin(),
      env[a].present_ideas.end(),
      i),
    env[a].present_ideas.end()
  );
}

bool Networkland::check_idea(const vertex_desc& a, Idea* i) {
  return std::find(
    env[a].present_ideas.begin(),
    env[a].present_ideas.end(), i
  ) != env[a].present_ideas.end();
}

bool Networkland::is_occupied(const vertex_desc& a){
  return !env[a].present_ideas.empty();
}

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
