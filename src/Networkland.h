#pragma once

#include <vector>
#include <algorithm>

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
  int id;
  //! stores x-axis coordinate of the Vertex
  double x;
  //! stores y-axis coordinate of the Vertex
  double y;
  //! index of interest - weight value of Vertex
  double ioi = -1;
  //! list of ideas that currently occupy the Vertex
  std::vector<Idea*> present_ideas;
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
    //! get adjacent vertices of an input vertex in graph
    std::vector<vertex_desc> get_adjacent_vertices(vertex_desc v);
    //! get distance value between two input vertices in graph
    double get_distance_between_two_vertices(
        const vertex_desc& a, const vertex_desc& b
      );
    //! check if two vertices are adjacent in graph
    bool are_adjacent(const vertex_desc& a, const vertex_desc& b);
    //! get ioi value of Vertex in graph
    double get_vertex_ioi(const vertex_desc& a);
    //! set ioi value of Vertex in graph
    void set_vertex_ioi(const vertex_desc& a, double new_ioi);
    //! get number of ideas occupying the Vertex
    size_t get_num_ideas(const vertex_desc& a);
    //! get Idea with smallest power value occupying the Vertex
    Idea* get_weakest_idea(const vertex_desc& a);
    //! add Idea to Vertex: Occupation
    void push_idea(const vertex_desc& a, Idea* i);
    //! remove Idea from Vertex
    void erase_idea(const vertex_desc& a, Idea* i);
    //! check if Idea is present in Vertex
    bool check_idea(const vertex_desc& a, Idea* i);
    //! check if the Vertex is occupied by any Ideas
    bool is_occupied(const vertex_desc& a);

    // std::string export_graph();

    private:
    //! stores graph (from boost graph library)
    graph_t env;
};
