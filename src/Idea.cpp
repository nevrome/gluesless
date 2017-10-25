#include "Idea.h"

#include <algorithm>

#include "global.h"

Idea::Idea(
  int id,
  int pow,
  int fec,
  int fid,
  int lon,
  Networkland* real,
  std::vector<vertex_desc> initial_idea_start_pos
) {
  this->identity = id;
  this->power = pow;
  this->fecundity = fec;
  this->fidelity = fid;
  this->longevity = lon;
  this->age_in_timesteps = 1;
  this->realworld = real;
  this->vertices = initial_idea_start_pos;
  // write ownership via id into vertices
  for (auto& p1 : this->vertices) {
    real->push_idea(p1, this);
  }
}

int Idea::get_identity() { return this->identity; }
void Idea::set_identity(int id) { this->identity = id; }
bool Idea::is_alive() { return this->alive; }
void Idea::die() {
  // set alive flag to false
  this->alive = false;
  // delete information in occupied vertices
  for (auto& p1 : this->vertices) {
    realworld->erase_idea(p1, this);
  }
  // delete information about occupied vertices
  this->vertices.clear();
}
int Idea::get_power() { return this->power; }
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
  realworld->push_idea(victim_hex, this);
  // increase fecundity, if ioi of victim vertex is > -1, else reduce it
  if (realworld->get_vertex_ioi(victim_hex) > -1) {
    this->fecundity = this->fecundity + 3;
  } else {
    if (randunifrange(0, 100) > 10) {
      this->fecundity--;
    }
  }
  // reduce ioi of victim_hex
  realworld->set_vertex_ioi(victim_hex, 1);
}

void Idea::fight(Idea* enemy, vertex_desc victim_hex) {
  //Rcpp::Rcout << this->fidelity << " vs. " << enemy->fidelity << std::endl;

  // fight decision
  if (this->power >= enemy->power) {
    // if this idea wins:
    // add new vertex to this idea
    this->vertices.push_back(victim_hex);
    // change occupation vector of vertex
    realworld->erase_idea(victim_hex, enemy);
    realworld->push_idea(victim_hex, this);
    // remove vertex from vertices vector of the enemy
    std::vector<vertex_desc>::iterator position = std::find(
      enemy->vertices.begin(), enemy->vertices.end(), victim_hex
    );
    enemy->vertices.erase(position);
    if (enemy->vertices.size() <= 0) {
      enemy->die();
    }
    // reduce fecundity
    // if (randunifrange(0, 100) > 90) {
    //   this->fecundity--;
    // }
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
  std::vector<vertex_desc> adjacentvecs2;
  std::vector<vertex_desc> adjacentvecs3;
  std::vector<vertex_desc> possible_victims;
  std::vector<double> distances;
  std::vector<double> victim_ioi;
  //double mindist;
  bool first_search_check = true;

  // iterate through all vertices occupied by the idea
  for (auto& p1 : own_vertices) {
    // set value of possible ioi to zero for this first vertex
    double max_possible_ioi = 0;
    size_t count_with_ioi = 0;
    // get neighbouring vertices of the current vertex
    adjacentvecs = realworld->get_adjacent_vertices(p1);
    // iterate through all neighbouring vertices of the current vertex
    for (auto& p2 : adjacentvecs) {
      // check, if current neighbouring vertex is already part of the idea
      if (!realworld->check_idea(p2, this)) {
        // if yes, then skip, else:
        // store current neighbouring vertex
        possible_victims.push_back(p2);
        // get the distance value between the current vertex and the current
        // neighbouring vertex
        distances.push_back(realworld->get_distance_between_two_vertices(p1, p2));
        // get the ioi sum of the neighbouring vertices of the current vertex
        double cur_ioi = realworld->get_vertex_ioi(p2);
        if (cur_ioi != -1) {count_with_ioi++;}
        max_possible_ioi += cur_ioi;
        adjacentvecs2 = realworld->get_adjacent_vertices(p2);
        for (auto& p3 : adjacentvecs2) {
          if (!realworld->check_idea(p3, this)) {
            cur_ioi = realworld->get_vertex_ioi(p3);
            if (cur_ioi != -1) {count_with_ioi++;}
            max_possible_ioi += cur_ioi;
            adjacentvecs3 = realworld->get_adjacent_vertices(p3);
            for (auto& p4 : adjacentvecs3) {
              if (!realworld->check_idea(p4, this)) {
                cur_ioi = realworld->get_vertex_ioi(p4);
                if (cur_ioi != -1) {count_with_ioi++;}
                max_possible_ioi += cur_ioi;
              }
            }
          }
        }
        if (count_with_ioi < 2) {count_with_ioi = 1;}
        victim_ioi.push_back(max_possible_ioi/count_with_ioi);
      }
    }
  }

  // select actual victim from possible victims
  // 1. sort ioi sum vector
  std::vector<size_t> ioi_index_sorted = sort_indexes(victim_ioi);
  // descending
  std::reverse(ioi_index_sorted.begin(), ioi_index_sorted.end());

  vertex_desc selected_victim;
  bool selection_done = false;

  // 2. make decision
  // focus on ioi
  if (randunifrange(0, 100) > 10) {
    // loop over every possible victim in the order of descending ioi sum
    for (auto p5 : ioi_index_sorted) {
      // distance influence
      if (randunifrange(0, 100) > (20 * distances[p5])) {
        selected_victim = possible_victims[p5];
        selection_done = true;
        break;
      }
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

Idea* Idea::split(int new_id) {
  // split vertices of currently splitting idea
  // create new vertex vectors
  std::vector<vertex_desc> v1 = this->vertices;
  std::vector<vertex_desc> v2;
  v2.reserve(100);
  // select random starting vertex in v1 (rebel)
  int start_rebel_index = randunifrange(0, v1.size() - 1);
  // move starting vertex from v1 to v2
  v2.push_back(v1[start_rebel_index]);
  v1.erase(v1.begin() + start_rebel_index);
  // loop to move half the vertices of v1 to v2 - defines number of rebels
  for (int p1 = 1; p1 <= (v1.size() / 2); p1++) {
    // loop to search for neighbour vectors of already rebellious vertices
    for (int p3 = 0; p3 < v1.size(); p3++) {
      int possible_rebel_index = p3;
      vertex_desc possible_rebel = v1[possible_rebel_index];
      // check, if this vertex is adjacent to an already rebellious vertex
      for (auto& p2 : v2) {
        if (realworld->are_adjacent(p2, possible_rebel)) {
          v2.push_back(possible_rebel);
          v1.erase(v1.begin() + possible_rebel_index);
          break;
        }
      }
    }
  }
  // create new idea with modified characteristics of the old idea
  int shared_fecundity = (this->fecundity / 2) * 1.2;
  Idea* newidea = new Idea(
    new_id,
    shared_fecundity,
    this->power + randunifrange(-1, 1),
    this->fidelity + randunifrange(-1, 1),
    this->longevity + randunifrange(-1, 1),
    realworld,
    v2
  );
  // reduce expansion of old idea
  this->vertices = v1;
  for (auto& p4 : v2) {
    realworld->erase_idea(p4, this);
  }
  // set age of old idea back to zero
  this->age_in_timesteps = 0;
  // adjust fecundity of old idea
  this->fecundity = shared_fecundity;

  return newidea;
}

//! An Idea grows older
void Idea::age() {
  this->age_in_timesteps++;
}
