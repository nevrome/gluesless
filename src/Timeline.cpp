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
  this->ideas.push_back(current->get_ideas());
  this->idea_regions.push_back(current->get_idea_regions());
  this->idea_parts.push_back(current->get_idea_parts());

}

SEXP Timeline::export_as_R_list() {

  using namespace Rcpp;

  // create R list to store the result
  List res;

  // add Numeric vector with the number_alive_ideas development to the resultlist
  //res["number_of_ideas"] = this->number_alive_ideas;

  // create vectors that will form the columns of the result data.frame
  // The result is structured to contain the expansion values of individual ideas for
  // every timestep. One observation could be for example: In timestep 50 cremation
  // occupies 0.48/1 of region Jutland. The result data.frame is therefore in
  // an extremly tall, tidy format.
  std::vector<int> timestep;
  timestep.reserve(100000);
  std::vector<std::string> idea_name;
  idea_name.reserve(100000);
  std::vector<std::string> region_name;
  region_name.reserve(100000);
  std::vector<double> proportion;
  proportion.reserve(100000);

  int count = 2500;
  // get pointer to the first idea list in the idea identity vector
  auto it_id_1 = ideas.cbegin();
  auto it_reg_1 = idea_regions.cbegin();

  // time loop
  for (auto it_par_1 : idea_parts) {

      auto it_id_2 = (it_id_1)->cbegin();
      auto it_reg_2 = (it_reg_1)->cbegin();

      // idea loop
      for (auto it_par_2: it_par_1) {

        auto it_reg_3 = (it_reg_2)->cbegin();

        // region + proporsion loop
        for (auto it_par_3: it_par_2) {

          // finally extract the essential values and write the rows in the
          // result vectors
          timestep.push_back(count);
          idea_name.push_back(*it_id_2);
          region_name.push_back(*it_reg_3);
          proportion.push_back(it_par_3);

          it_reg_3++;

        }

      it_id_2++;
      it_reg_2++;
    }

    it_id_1++;
    it_reg_1++;
    count--;
  }

  // construct data.frame and add to export list
  res["idea_exp"] = Rcpp::DataFrame::create(
    _["timestep"] = timestep,
    _["idea"] = idea_name,
    _["region_name"] = region_name,
    _["proportion"] = proportion,
    _["stringsAsFactors"] = false
  );

  return res;
}
