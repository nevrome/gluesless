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

int Aether::get_ideanumber() {
  return this->mindspace.size();
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
      1,
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

  // create offset vector
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
      double growth_dbl = (std::log2(current_fecundity) + 0.5) * 2;
      int growth = (int) std::round(growth_dbl);
      Rcpp::Rcout << growth << std::endl;
      for (int p1 = 1; p1 <= growth; p1++) {
      // check if the idea is not already everywhere (total domination)
        if ((*it)->get_vertices().size() < num_ver) {
          // if so:
          // the idea decides where to go
          vertex_desc victim_hex = (*it)->direction_selection();
          // check whether the victim vertex is already occupied
          int potential_enemy = realworld->get_vertex_occupying_idea_id(victim_hex);
          if (potential_enemy == -1) {
            // if no: just infect it
            (*it)->infect(victim_hex);
          } else {
            // if yes: fight against the enemy
            (*it)->fight(
              // select enemy
              mindspace[potential_enemy],
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
