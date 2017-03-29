#ifndef _gluesless_RCPP_Networkland_H
#define _gluesless_RCPP_Networkland_H

#include <Rcpp.h>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/properties.hpp>
#include <vector>

#include "Idea.h"

using namespace boost;
using namespace Rcpp;
using namespace std;

// define graph
struct Vertex {
  std::string name;
  vector<Idea*> mind;
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

class Networkland {

    public:
    //constructor
    Networkland(std::string graphstring);

    // getter
    graph_t get_graph();

    // R-exporter
    // std::string export_graph();

    // developer
    Networkland develop();

    private:
    // attributes
    graph_t env;
};

#endif