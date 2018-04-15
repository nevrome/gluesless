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
// static inline std::ostream& operator<<(std::ostream& os, std::vector<dummy*> const& i) {
//   // here I would have to do something, if this feature would be necessary
//   return os;
// }
// static inline std::istream& operator>>(std::istream& is, std::vector<dummy*> const& i) {
//   // here I would have to do something, if this feature would be necessary
//   return is;
// }

Networkland::Networkland(const std::string& graphml_file_path) {

  // create empty graph object
  graph_t graph(0);

  // add graph properties
  dynamic_properties dp(ignore_other_properties);
  dp.property("name",               get(&Vertex::name,            graph));
  dp.property("weight",             get(&Edge::weight,            graph));

  // // graph name
  // ref_property_map<graph_t *, std::string> gname(
  //     get_property(graph, graph_name)
  //   );
  // dp.property("graph_name", gname);

  std::ifstream file(graphml_file_path);
  if (file)
  {

    /*
     * Get the size of the file
     */
    file.seekg(0,std::ios::end);
    std::streampos          length = file.tellg();
    file.seekg(0,std::ios::beg);

    /*
     * Use a vector as the buffer.
     * It is exception safe and will be tidied up correctly.
     * This constructor creates a buffer of the correct length.
     *
     * Then read the whole file into the buffer.
     */
    std::vector<char>       buffer(length);
    file.read(&buffer[0],length);

    /*
     * Create your string stream.
     * Get the stringbuffer from the stream and set the vector as it source.
     */
    std::stringstream       localStream;
    localStream.rdbuf()->pubsetbuf(&buffer[0],length);

    /*
     * Note the buffer is NOT copied, if it goes out of scope
     * the stream will be reading from released memory.
     */

    // read graph from string
    read_graphml(localStream, graph, dp);

    // add properties to graph that are not part of the input
    //dp.property("dummy",            get(&Vertex::dummy,             graph));

    this->env = graph;
  }
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
  for (tie(ai, ai_end) = adjacent_vertices(v, env); ai != ai_end; ai++) {
    res.push_back(index[*ai]);
  }
  return res;
}

double Networkland::get_weight_between_two_vertices(
    const vertex_desc& a, const vertex_desc& b
  ) {
  // create a pair to store the edge iterators
  std::pair<edge_desc, bool> edgepair;
  edgepair = edge(a, b, env);
  return env[edgepair.first].weight;
}

bool Networkland::are_adjacent(
    const vertex_desc& a, const vertex_desc& b
  ) {
  return edge(a, b, env).second;
}

std::pair<vertex_iter, vertex_iter> Networkland::get_all_vertices() {
  return vertices(env);
}

std::string Networkland::get_name(const vertex_desc& a) {
  return env[a].name;
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
