#ifndef _gluesless_RCPP_Networkland_H
#define _gluesless_RCPP_Networkland_H

// [[Rcpp::depends(BH)]]

#include <Rcpp.h>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include "Networkland.h"

using namespace boost;
using namespace Rcpp;
using namespace std;

typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;

class Networkland {


  public:
    //constructor
    Networkland();

    // getter
    Graph get_graph();

    // R-exporter
    std::string export_graph();

    // develop functions
    //void develop();
    //void develop_udef(Function pop_develop_udef);

  private:
    // attributes
    Graph env;
};

#endif