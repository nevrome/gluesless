#ifndef _gluesless_RCPP_Networkland_H
#define _gluesless_RCPP_Networkland_H

#include <Rcpp.h>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/properties.hpp>
#include <vector>

using namespace boost;
using namespace Rcpp;
using namespace std;

// define graph
struct Vertex {
  int id;
  double x;
  double y;
};

struct Edge {
  double distance;
};

typedef property<graph_name_t, std::string> Complete_Graph;

typedef adjacency_list<listS, vecS, undirectedS,
                       Vertex,
                       Edge,
                       Complete_Graph>
        graph_t;

typedef graph_traits<graph_t>::vertex_iterator vertex_iter;
typedef graph_traits<graph_t>::vertex_descriptor Vertexdesc;
typedef graph_traits<graph_t>::edge_descriptor Edgedesc;
typedef graph_traits<graph_t> GraphTraits;
typedef property_map<graph_t, vertex_index_t>::type IndexMap;

class Networkland {

    public:
    //constructor
    Networkland(std::string graphstring);
    Networkland(graph_t newenv);

    // getter
    graph_t get_graph();
    int get_number_of_vertices();
    vector<Vertexdesc> get_adjacent_vertices(Vertexdesc v);
    double get_distance_between_two_vertices(Vertexdesc a, Vertexdesc b);

    // R-exporter
    // std::string export_graph();

    // developer
    // Networkland develop();

    private:
    // attributes
    graph_t env;
};

#endif