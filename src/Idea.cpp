#include "Idea.h"

#include <algorithm>

#include "global.h"

Idea::Idea(
  int id,
  int fec,
  int fid,
  int lon,
  Networkland* real,
  std::vector<vertex_desc> birth_vertices
) {
  this->identity = id;
  this->fecundity = fec,
  this->fidelity = fid,
  this->longevity = lon,
  this->age_in_timesteps = 1;
  this->realworld = real;
  this->vertices = birth_vertices;
  // write ownership via id into vertices
  for (auto& veri : birth_vertices) {
    real->set_vertex_occupying_idea_id(veri, id);
  }
}

int Idea::get_identity() { return this->identity; }
void Idea::set_identity(int id) { this->identity = id; }
bool Idea::is_alive() { return this->alive; }
void Idea::die() {
  // set alive flag to false
  this->alive = false;
  // delete information in occupied vertices
  for (auto& veri : this->vertices) {
    realworld->set_vertex_occupying_idea_id(veri, -1);
  }
  // delete information about occupied vertices
  this->vertices.clear();
}
int Idea::get_age(){ return this->age_in_timesteps; }
int Idea::get_fecundity() { return this->fecundity; }
int Idea::get_fidelity() { return this->fidelity; }
int Idea::get_longevity() { return this->longevity; }

std::vector<vertex_desc> Idea::get_vertices() {
  return this->vertices;
}

void Idea::infect(vertex_desc victim_hex) {
  // add hex to idea
  vertices.push_back(victim_hex);
  // install idea in hex
  realworld->set_vertex_occupying_idea_id(victim_hex, this->identity);
  // increase fecundity
  if (realworld->get_vertex_ioi(victim_hex) >= -1) {
    this->fecundity++;
  }
}

void Idea::fight(Idea* enemy, vertex_desc victim_hex) {
  //Rcpp::Rcout << this->fidelity << " vs. " << enemy->fidelity << std::endl;

  // fight decision
  if (this->fidelity >= enemy->fidelity) {
    // if this idea wins:
    // add new vertex to this idea
    this->vertices.push_back(victim_hex);
    // change occupation flag of vertex
    realworld->set_vertex_occupying_idea_id(victim_hex, this->identity);
    // remove vertex from vertices vector of the enemy
    //enemy->vertices
    std::vector<vertex_desc>::iterator position = std::find(
      enemy->vertices.begin(), enemy->vertices.end(), victim_hex
    );
    if (position != enemy->vertices.end()) {
      // Rcpp::Rcout << enemy->vertices.size() << std::endl;
      // sleep(1);
      // if (enemy->vertices.size() <= 1) {
      //   enemy->die();
      // } else {
      enemy->vertices.erase(position);
      if (enemy->vertices.size() <= 0) {
        enemy->die();
      }
    }
  }
}

vertex_desc Idea::direction_selection() {

  // get vertices of current idea and shuffle them randomly to prevent
  // linear spread because of victim selection algorithm (see below)
  std::vector<vertex_desc> own_vertices = this->vertices;
  std::random_shuffle(
    own_vertices.begin(),
    own_vertices.end(),
    randWrapper
  );

  // create empty objects to store intermediate results
  std::vector<vertex_desc> adjacentvecs;
  std::vector<vertex_desc> possible_victims;
  std::vector<double> distances;
  std::vector<double> victim_ioi;
  //double mindist;
  bool first_search_check = true;

  // iterate through all vertices occupied by the idea
  for (auto& p1 : own_vertices) {
    // get neighbouring vertices of the current vertex
    adjacentvecs = realworld->get_adjacent_vertices(p1);
    // iterate through all neighbouring vertices of the current vertex
    for (auto& p2 : adjacentvecs) {
      // check, if current neighbouring vertex is not already part of the idea
      // if it's part, then skip, else:
      if (!(find(own_vertices.begin(), own_vertices.end(), p2) != own_vertices.end())) {
        // get the distance value between the two vertices
        // search for victim with smallest distance
        possible_victims.push_back(p2);
        distances.push_back(realworld->get_distance_between_two_vertices(p1, p2));
        victim_ioi.push_back(realworld->get_vertex_ioi(p2));
      }
    }
  }

  // select actual victim from possible victims
  // 1. search for index of possible victim with smallest distance
  int smallest_dist_index = std::distance(
    distances.begin(),
    std::min_element(
      distances.begin(),
      distances.end()
    )
  );
  int smallest_dist = distances[smallest_dist_index];

  // 2. search for index of possible victim with biggest ioi
  int biggest_ioi_index = std::distance(
    victim_ioi.begin(),
    std::max_element(
      victim_ioi.begin(),
      victim_ioi.end()
    )
  );
  int biggest_ioi = victim_ioi[biggest_ioi_index];

  vertex_desc selected_victim;
  bool selection_done = false;

  // 3. make decision
  if (!selection_done & (randunifrange(0, 101) > 20)) {
      selected_victim = possible_victims[biggest_ioi_index];
      selection_done = true;
  }

  if (!selection_done & (randunifrange(0, 101) > 50)) {
    if (randunifrange(0, 101) > 30 * smallest_dist) {
      selected_victim = possible_victims[smallest_dist_index];
      selection_done = true;
    }
  }

  if (!selection_done) {
    selected_victim = possible_victims[randunifrange(0, possible_victims.size() - 1)];
    selection_done = true;
  }

  return selected_victim;

  // when the previous loop found a victim it can become part of the idea
  //Rcpp::Rcout << "test" << std::endl;
    // get probability decision about where an idea actually grows
    // dependend on the edge distance value of the victim node
    //if (randunifrange(0, 101) > mindist*100) {
  //return possible_victims[randunifrange(0, possible_victims.size() - 1)];
    //}
}



//void Idea::fight();

Idea* Idea::split(int new_id) {
  // split vertices of currently splitting idea
  std::vector<vertex_desc> v1 = this->vertices;
  std::vector<vertex_desc> v2(
      std::make_move_iterator(v1.begin() + v1.size()/2),
      std::make_move_iterator(v1.end()));
  v1.erase(v1.begin() + v1.size()/2, v1.end());
  // create new idea with modified characteristics of the old idea
  Idea* newidea = new Idea(
    new_id,
    this->fecundity,
    this->fidelity + randunifrange(-1, 1),
    this->longevity + randunifrange(-1, 1),
    realworld,
    v2
  );
  // reduce expansion of old idea
  this->vertices = v1;
  // set age of old idea back to zero
  this->age_in_timesteps = 0;

  return newidea;
}

//! An Idea grows older
void Idea::age() {
  this->age_in_timesteps++;
}
