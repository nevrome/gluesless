#include <cstdlib>
#include <math.h>
#include <iostream>

#include "Snap.h"

//#include <progress.hpp>
//#include <progress_bar.hpp>

#include "Idea.h"
//#include "Networkland.h"
#include "Timeline.h"

//! main
/*!
  main method
  */
  
int main(int argc, char* argv[]){
  
  typedef PUNGraph PGraph;
  
  PGraph G = PGraph::TObj::New();
  for (int n = 0; n < 10; n++) {
    G->AddNode(); // if no parameter is given, node ids are 0,1,...,9
  }
  G->AddEdge(0, 1);
  for (int e = 0; e < 10; e++) {
    const int NId1 = G->GetRndNId();
    const int NId2 = G->GetRndNId();
    if (G->AddEdge(NId1, NId2) != -2) {
      printf("  Edge %d -- %d added\n", NId1,  NId2); }
    else {
      printf("  Edge %d -- %d already exists\n", NId1, NId2); }
  }
  IAssert(G->IsOk());
  
  std::string graphml_file_path = argv[1];
  std::cout << graphml_file_path << std::endl;
  
  // igraph::igraph_t graph;
  
  std::stringstream buffer;
  
  std::ifstream file(graphml_file_path);
  buffer << file.rdbuf();
  
  // int igraph_read_graph_graphml(graph, buffer, 0);
  
  file.close();
  
  // std::string graphml_file_path

  // load modell builder
  // Rcpp::S4 mb(model_builder);
  
  // create start environment
  // SEXP graphml_file = wrap(mb.slot("networkland_env"));
  // std::string graphml_file_path = Rcpp::as<std::string>(graphml_file);
  // SEXP iterations = wrap(mb.slot("number_iterations"));
  // int iter = Rcpp::as<int>(iterations);
  // SEXP ideas_list = wrap(mb.slot("ideas_list"));
  // std::vector<std::string> ideas = Rcpp::as<std::vector<std::string>>(ideas_list);
  // SEXP ideas_proportions_matrix = wrap(mb.slot("ideas_proportions_matrix"));
  // Rcpp::NumericMatrix ideas_proportions = Rcpp::as<Rcpp::NumericMatrix>(ideas_proportions_matrix);
  // SEXP start_pos = wrap(mb.slot("initial_idea_starting_positions"));
  // std::vector<long unsigned int> idea_start_pos_int = Rcpp::as<std::vector<long unsigned int>>(start_pos);
  // std::vector<vertex_desc> idea_start_pos = idea_start_pos_int;

  // Realwelt
  //Networkland* real = new Networkland(graphml_file_path);

  // Geistwelt
  // Aether* overmind = new Aether(real);

  // Zeit
  // Timeline* thyme = new Timeline(overmind);

  // // Ideas
  // for (size_t i = 0; i < ideas.size(); i++) {
  //   std::string idea_name = ideas[i];
  //   NumericVector proportions_nvec = ideas_proportions(_,i);
  //   std::vector<double> proportions_vec = Rcpp::as<std::vector<double>>(proportions_nvec);
  //   Idea* new_idea = new Idea(idea_name, real, proportions_vec);
  //   overmind->add_idea_to_mindspace(new_idea);
  // }
  //
  // // set competing idea
  // if (overmind->get_size_of_mindspace() == 2) {
  //   overmind->get_idea_from_mindspace(0)->add_competing_idea(overmind->get_idea_from_mindspace(1));
  //   overmind->get_idea_from_mindspace(1)->add_competing_idea(overmind->get_idea_from_mindspace(0));
  // } else {
  //   // not implemented
  // }
  //
  // // develop
  // Progress p(iter, true);
  // for (int i = 0; i < iter; i++) {
  //   thyme->develop(overmind);
  //   if (Progress::check_abort()) {break;}
  //   p.increment();
  // }
  //
  // List res = thyme->export_as_R_list();

  // delete real;
  // delete overmind;
  // delete thyme;

  return 0;
}
