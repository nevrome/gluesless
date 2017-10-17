#include <math.h>

#include "global.h"
#include "Timeline.h"
#include "Aether.h"

Timeline::Timeline(Aether* start) {
}

void Timeline::develop(Aether* current) {

  // develop Aether
  current->develop();

  // query new Aether values to be stored in Timeline
  this->ideanumber.push_back(current->get_ideanumber());
  this->ideas.push_back(current->get_ideas());
  this->idea_vertices.push_back(
      current->get_idea_vertices()
  );
  this->fecundities.push_back(current->get_fecundities());
  this->fidelities.push_back(current->get_fidelities());
  this->longevities.push_back(current->get_longevities());

}

SEXP Timeline::export_as_R_list() {

  using namespace Rcpp;

  // create R list to store the result
  List res;

  // add Numeric vector with the ideanumber development to the resultlist
  res["number_of_ideas"] = this->ideanumber;

  // create vectors that will form the columns of the result data.frame
  // The result is structured to contain the positions of individual ideas for
  // every timestep. One observation could be for example: In timestep 50 idea
  // 38 occupies vertex position 456. The result data.frame is therefore in
  // an extremly tall, tidy format.
  std::vector<int> timestep;
  timestep.reserve(100000);
  std::vector<int> id;
  id.reserve(100000);
  std::vector<int> vert;
  vert.reserve(100000);
  std::vector<int> fecu;
  fecu.reserve(100000);
  std::vector<int> fide;
  fide.reserve(100000);
  std::vector<int> longe;
  longe.reserve(100000);

  // determine export timestep resolution depending on number of iterations
  //int iter = this->ideanumber.size();
  //int am = pow(10, get_number_of_digits(iter) - 2);

  int count = 0;
  // get pointer to the first idea list in the idea identity vector
  auto it_id_1 = ideas.cbegin();
  // ... and the other idea property vectors
  auto it_fecu_1 = fecundities.cbegin();
  auto it_fide_1 = fidelities.cbegin();
  auto it_longe_1 = longevities.cbegin();

  // loop over idea positions vector
  for (auto& it_vert_1 : idea_vertices) {

    // only export every xth step and first and last
    //if(count % am == 0 || count == iter - 1) {
      // get pointer to the first idea in the idea list in the idea identity vector
      auto it_id_2 = (*it_id_1).cbegin();
      auto it_fecu_2  = (*it_fecu_1).cbegin();
      auto it_fide_2 = (*it_fide_1).cbegin();
      auto it_longe_2 = (*it_longe_1).cbegin();

      // loop over idea list in positions vector
      for (auto& it_vert_2 : it_vert_1) {
        // loop over individual positions in the idea lists in position vector
        for (auto& it_vert_3 : it_vert_2) {

          // finally extract the essential values and write the rows in the
          // result vectors
          timestep.push_back(count);
          id.push_back(*it_id_2);
          vert.push_back(it_vert_3);
          fecu.push_back(*it_fecu_2);
          fide.push_back(*it_fide_2);
          longe.push_back(*it_longe_2);

        }
      it_id_2++;
      it_fecu_2++;
      it_fide_2++;
      it_longe_2++;
      }
    //}
  it_id_1++;
  it_fecu_1++;
  it_fide_1++;
  it_longe_1++;
  count++;
  }

  // construct data.frame and add to export list
  res["idea_exp"] = Rcpp::DataFrame::create(
    _["timestep"] = timestep,
    _["ideas"] = id,
    _["fecundity"] = fecu,
    _["fidelity"] = fide,
    _["longevity"] = longe
  );

  return res;
}
