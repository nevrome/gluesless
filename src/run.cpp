// [[Rcpp::depends(RcppProgress)]]

#include <cstdlib>
#include <math.h>

#include <Rcpp.h>
#include <progress.hpp>
#include <progress_bar.hpp>

#include "Idea.h"
#include "Networkland.h"
#include "Timeline.h"

using namespace Rcpp;

//' run model
//'
//' General run method. Something like the main function of a usual
//' c++-program. Runs model with input parameters and gives results
//' directly back to R.
//'
//' @param model_builder model_builder-object with parameters
//'
//' @return
//' List with different diagnostic values
//'
//' @export
// [[Rcpp::export]]
SEXP run(SEXP model_builder){

  // load modell builder
  Rcpp::S4 mb(model_builder);

  // create start environment
  SEXP graphstr = wrap(mb.slot("networkland_env"));
  std::string graphstring = Rcpp::as<std::string>(graphstr);
  SEXP iterations = wrap(mb.slot("number_iterations"));
  int iter = Rcpp::as<int>(iterations);
  SEXP ideas_list = wrap(mb.slot("ideas_list"));
  std::vector<std::string> ideas = Rcpp::as<std::vector<std::string>>(ideas_list);
  SEXP ideas_proportions_matrix = wrap(mb.slot("ideas_proportions_matrix"));
  Rcpp::NumericMatrix ideas_proportions = Rcpp::as<Rcpp::NumericMatrix>(ideas_proportions_matrix);
  // SEXP start_pos = wrap(mb.slot("initial_idea_starting_positions"));
  // std::vector<long unsigned int> idea_start_pos_int = Rcpp::as<std::vector<long unsigned int>>(start_pos);
  // std::vector<vertex_desc> idea_start_pos = idea_start_pos_int;

  // Realwelt
  Networkland* real = new Networkland(graphstring);

  // Geistwelt
  Aether* overmind = new Aether(real);

  // Zeit
  Timeline* thyme = new Timeline(overmind);

  // Ideas
  for (size_t i = 0; i < ideas.size(); i ++) {
    std::string idea_name = ideas[i];
    NumericVector proportions_nvec = ideas_proportions(_,i);
    std::vector<double> proportions_vec = Rcpp::as<std::vector<double>>(proportions_nvec);
    Idea* new_idea = new Idea(idea_name, real, proportions_vec);
    overmind->add_idea_to_mindspace(new_idea);
  }

  // set competing idea
  if (overmind->get_size_of_mindspace() == 2) {
    overmind->get_idea_from_mindspace(0)->add_competing_idea(overmind->get_idea_from_mindspace(1));
    overmind->get_idea_from_mindspace(1)->add_competing_idea(overmind->get_idea_from_mindspace(0));
  } else {
    // not implemented
  }

  // develop
  Progress p(iter, true);
  for (int i = 0; i < iter; i++) {
    thyme->develop(overmind);
    if (Progress::check_abort()) {break;}
    p.increment();
  }

  List res = thyme->export_as_R_list();

  delete real;
  delete overmind;
  delete thyme;

  return res;
}
