#ifndef _gluesless_RCPP_Networkland_H
#define _gluesless_RCPP_Networkland_H

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
  std::string name, gender;
  double age;
};

struct Edge
{
  double friendship;
  double advice;
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
    //Networkland();
    Networkland(std::string graphstring);

    // getter
    graph_t get_graph();
    //dynamic_properties get_graph_properties();

    // R-exporter
    std::string export_graph();

  private:
    // attributes
    graph_t env;
    //dynamic_properties prop;
};

#endif