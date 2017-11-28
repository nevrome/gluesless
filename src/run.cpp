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
int run(SEXP model_builder){
//SEXP run(SEXP model_builder){

  // load modell builder
  Rcpp::S4 mb(model_builder);

  // create start environment
  SEXP graphstr = wrap(mb.slot("networkland_env"));
  std::string graphstring = Rcpp::as<std::string>(graphstr);
  SEXP iterations = wrap(mb.slot("number_iterations"));
  int iter = Rcpp::as<int>(iterations);
  // SEXP start_pos = wrap(mb.slot("initial_idea_starting_positions"));
  // std::vector<long unsigned int> idea_start_pos_int = Rcpp::as<std::vector<long unsigned int>>(start_pos);
  // std::vector<vertex_desc> idea_start_pos = idea_start_pos_int;

  // Realwelt
  Networkland* real = new Networkland(graphstring);

  // Geistwelt
  Aether* overmind = new Aether(real);

  // Zeit
  Timeline* thyme = new Timeline(overmind);

  // Ideen
  std::vector<double> v = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
  Idea* cremation = new Idea("cremation", real, v);
  Idea* inhumation = new Idea("inhumation", real, v);
  Idea* flat = new Idea("flat", real, v);
  Idea* mound = new Idea("mound", real, v);

  overmind->add_idea_to_mindspace(cremation);
  overmind->add_idea_to_mindspace(inhumation);
  overmind->add_idea_to_mindspace(flat);
  overmind->add_idea_to_mindspace(mound);

  // develop
  Progress p(iter, true);
  for (int i = 0; i < iter; i++) {
    thyme->develop(overmind);
    if (Progress::check_abort()) {break;}
    p.increment();
  }

  //List res = thyme->export_as_R_list();

  delete real;
  delete overmind;
  delete thyme;
  delete cremation;
  delete inhumation;
  delete flat;
  delete mound;

  return 1;
}
