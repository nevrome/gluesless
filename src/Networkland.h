#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/properties.hpp>

#include <Rcpp.h>

class Idea;

//! Node in the graph of a Networkland
/*!
 Could represent Individuals, Settlements, Areas etc..
 */
struct Vertex {
  //! stores identity of the Vertex
  std::string region_name;
  //! stores x-axis coordinate of the Vertex
  double x;
  //! stores y-axis coordinate of the Vertex
  double y;
  //! dummy
  //std::vector<dummy*> dummy;
};


//! Connecting line in the graph of a Networkland
/*!
 Could represent a spatial, cultural etc. relationship.
 */

struct Edge {
  //! stores distance value of the Edge
  double distance;
};

// boost graph typedefs

typedef boost::property<boost::graph_name_t, std::string> complete_graph;

typedef boost::adjacency_list<
          boost::listS,
          boost::vecS,
          boost::undirectedS,
          Vertex,
          Edge,
          complete_graph>
        graph_t;

typedef boost::graph_traits<graph_t> graph_trs;
typedef graph_trs::vertex_iterator vertex_iter;
typedef graph_trs::vertex_descriptor vertex_desc;
typedef graph_trs::edge_descriptor edge_desc;
typedef boost::property_map<graph_t, boost::vertex_index_t>::type index_map;

//! Real world represented with a network - ABM environment
/*!
 Could represent a spatial, cultural etc. network.
 */

class Networkland {

    public:
    Networkland(const std::string& graphstring);
    Networkland(graph_t newenv);

    //! get graph
    graph_t get_graph();
    //! get number of vertices of graph
    int get_number_of_vertices();
    //! get iterator pair to all vertices
    std::pair<vertex_iter, vertex_iter> get_all_vertices();
    //! get adjacent vertices of an input vertex in graph
    std::vector<vertex_desc> get_adjacent_vertices(vertex_desc v);
    //! get distance value between two input vertices in graph
    double get_distance_between_two_vertices(
        const vertex_desc& a, const vertex_desc& b
      );
    //! check if two vertices are adjacent in graph
    bool are_adjacent(const vertex_desc& a, const vertex_desc& b);
    //! get region name of vertex
    std::string get_region_name(const vertex_desc& a);

    // std::string export_graph();

    private:
    //! stores graph (from boost graph library)
    graph_t env;
};
