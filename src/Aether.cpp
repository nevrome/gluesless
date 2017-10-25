#include <math.h>

#include "Aether.h"

#include "global.h"

Aether::Aether(Networkland* real, std::vector<vertex_desc> idea_start_pos) {
  this->realworld = real;
  this->idea_id_counter = 0;
  this->initial_idea_start_pos = idea_start_pos;

}

int Aether::get_idea_id_counter() {
  return this->idea_id_counter;
}

void Aether::increment_idea_id_counter() {
  this->idea_id_counter++;
}

int Aether::get_number_alive_ideas() {
  // count if idea is alive
  int res = std::count_if(
    this->mindspace.begin(),
    this->mindspace.end(),
    //lambda expression!
    [](Idea* i){return i->is_alive();}
  );
  //Rcpp::Rcout << res << std::endl;
  return res;
}

std::vector<int> Aether::get_ideas() {
  std::vector<int> res;
  res.reserve(this->mindspace.size());
  for(auto& idx : this->mindspace) {
    res.push_back(idx->get_identity());
  }
  return res;
}

std::vector< std::vector<vertex_desc> > Aether::get_idea_vertices(){
  std::vector< std::vector <vertex_desc> > res;
  res.reserve(this->mindspace.size());
  for(auto& idx : this->mindspace) {
    res.push_back(idx->get_vertices());
  }
  return res;
}

std::vector<int> Aether::get_powers() {
  std::vector<int> res;
  res.reserve(this->mindspace.size());
  for(auto& idx : this->mindspace) {
    res.push_back(idx->get_power());
  }
  return res;
}

std::vector<int> Aether::get_fecundities() {
  std::vector<int> res;
  res.reserve(this->mindspace.size());
  for(auto& idx : this->mindspace) {
    res.push_back(idx->get_fecundity());
  }
  return res;
}

std::vector<int> Aether::get_fidelities() {
  std::vector<int> res;
  res.reserve(this->mindspace.size());
  for(auto& idx : this->mindspace) {
    res.push_back(idx->get_fidelity());
  }
  return res;
}

std::vector<int> Aether::get_longevities() {
  std::vector<int> res;
  res.reserve(this->mindspace.size());
  for(auto& idx : this->mindspace) {
    res.push_back(idx->get_longevity());
  }
  return res;
}


void Aether::develop() {

  // create convinient short
  auto& v = this->mindspace;

  // get number of vertices in the complente networkland graph
  // to later check for total domination of ideas
  int num_ver = boost::num_vertices(this->realworld->get_graph());


  // if no ideas are present, create the first one (simulation startup)
  if(v.size() == 0){
    Idea* newidea = new Idea(
      this->idea_id_counter,
      10,
      5,
      10,
      10,
      realworld,
      this->initial_idea_start_pos
    );
    // increase Aether id counter
    this->increment_idea_id_counter();
    // store new idea in mindspace
    v.push_back(newidea);
  }

  // create offset vector to shuffle order of ideas
  std::vector<int> offset;
  offset.reserve(v.size());
  for (size_t i=0u; i<v.size(); ++i) {
    offset.push_back(i);
  }
  random_shuffle(
    offset.begin(),
    offset.end(),
    randWrapper
  );

  // iterate over the ideas effectively shuffled by the offset
  for (auto& idx : offset) {
    auto it = v.begin() + idx;
    // check if idea is alive
    if (!(*it)->is_alive()) {
      // if not: skip the idea
      continue;
    }
    // check if the idea dies of old age
    if ((*it)->get_age() == (*it)->get_longevity()) {
      // if yes:
      // is the idea only present in one hexagon or already wiped out?
      if ((*it)->get_vertices().size() <= 1) {
        // if yes: the idea is actually removed
        (*it)->die();
      } else {
        // if no: the idea splits
        Idea* newidea = (*it)->split(this->idea_id_counter);
        this->increment_idea_id_counter();
        v.push_back(newidea);
      }
    } else {
      // if no:
      // the idea grows based on its fecundity
      // calculate growth based on fecundity with log2
      int current_fecundity = (*it)->get_fecundity();
      double growth_dbl = (std::log2(current_fecundity) + 0.5);
      int growth = (int) std::round(growth_dbl);
      // int growth = current_fecundity;
      //Rcpp::Rcout << growth << std::endl;
      // realize growth for every growth point
      for (int p1 = 1; p1 <= growth; p1++) {
      // check if the idea is not already everywhere (total domination)
        if ((*it)->get_vertices().size() < num_ver) {
          // if so:
          // the idea decides where to go
          vertex_desc victim_hex = (*it)->direction_selection();
          // check whether the victim vertex is already occupied
          if (!realworld->is_occupied(victim_hex) ||
              // this number sets degree of overlapping
              realworld->get_num_ideas(victim_hex) <= 2) {
            // if no: just infect it
            (*it)->infect(victim_hex);
          } else {
            // if yes: find enemy and fight against it
            (*it)->fight(
              // select enemy
              realworld->get_weakest_idea(victim_hex),
              victim_hex
            );
          }
        }
      }
      // the idea ages
      (*it)->age();
    }
  }


}
