#pragma once

#include <vector>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/properties.hpp>
#include <Rcpp.h>

//! Node in the graph of a Networkland
/*!
 Could represent Individuals, Settlements, Areas etc..
 */

struct Vertex {
  //! stores identity of the Node
  int id;
  //! stores x-axis coordinate of the Node
  double x;
  //! stores y-axis coordinate of the Node
  double y;
};


//! Connecting line in the graph of a Networkland
/*!
 Could represent a spatial, cultural etc. relationship.
 */

struct Edge {
  //! stores distance value of the Edge
  double distance;
};

typedef boost::property<boost::graph_name_t, std::string> Complete_Graph;

typedef boost::adjacency_list<
          boost::listS,
          boost::vecS,
          boost::undirectedS,
          Vertex,
          Edge,
          Complete_Graph>
        graph_t;

typedef boost::graph_traits<graph_t>::vertex_iterator vertex_iter;
typedef boost::graph_traits<graph_t>::vertex_descriptor Vertexdesc;
typedef boost::graph_traits<graph_t>::edge_descriptor Edgedesc;
typedef boost::graph_traits<graph_t> GraphTraits;
typedef boost::property_map<graph_t, boost::vertex_index_t>::type IndexMap;

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
    //! get adjacent vertices of an input vertex in graph
    std::vector<Vertexdesc> get_adjacent_vertices(Vertexdesc v);
    //! get distance value between two input vertices in graph
    double get_distance_between_two_vertices(
        Vertexdesc a, Vertexdesc b
      );

    // std::string export_graph();

    private:
    //! stores graph (from boost graph library)
    graph_t env;
};