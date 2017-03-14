#ifndef _gluesless_RCPP_Networkland_H
#define _gluesless_RCPP_Networkland_H

// [[Rcpp::depends(BH)]]

#include <Rcpp.h>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/properties.hpp>

using namespace boost;
using namespace Rcpp;
using namespace std;

struct Vertex
{
  std::string name, label, shape;
};

struct Edge
{
  std::string label;
  double weight;
};

typedef property<graph_name_t, std::string> Complete_Graph;
typedef adjacency_list<listS, vecS, bidirectionalS,
                       Vertex,
                       Edge,
                       Complete_Graph>
        graph_t;

class Networkland {


  public:
    //constructor
    //Networkland();
    Networkland(std::string graphstring);

    // getter
    graph_t get_graph();

    // R-exporter
    std::string export_graph();

    // develop functions
    //void develop();
    //void develop_udef(Function pop_develop_udef);

  private:
    // attributes
    graph_t env;
};

#endif