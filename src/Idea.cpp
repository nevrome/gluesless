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
int Idea::get_age(){ return this->age_in_timesteps; }
int Idea::get_fecundity() { return this->fecundity; }
int Idea::get_fidelity() { return this->fidelity; }
int Idea::get_longevity() { return this->longevity; }

std::vector<vertex_desc> Idea::get_vertices() {
  return this->vertices;
}

void Idea::grow() {
  try {
    vertex_desc victim_hex = this->direction_selection();
    Rcpp::Rcout << realworld->get_vertex_occupying_idea_id(victim_hex) << std::endl;
    if (realworld->get_vertex_occupying_idea_id(victim_hex) == -1) {
      this->infect(victim_hex);
    }
  } catch(std::string err) {
    Rcpp::Rcout << err << std::endl;
    // very bad practice: no cleanup
    std::exit(0);
  }

  //this->fight();
}

void Idea::infect(vertex_desc victim_hex) {
  vertices.push_back(victim_hex);
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
  vertex_desc victim;
  double mindist;
  bool total_domination_check = true;
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
        // obviously the current idea doesn't dominate everything
        if (total_domination_check) {
          total_domination_check = false;
        }
        // get the distance value between the two vertices
        double tempdist = realworld->get_distance_between_two_vertices(p1, p2);
        // search for victim with smallest distance
        // first loop iteration: choose the first one as victim
        if (first_search_check) {
          // Rcpp::Rcout << tempdist << std::endl;
          // Rcpp::Rcout << p2 << std::endl;
          mindist = tempdist;
          victim = p2;
          first_search_check = false;
        // further loop iterations:
        // check if tempdist actually smaller - if yes = select as new victim
        } else if (tempdist < mindist) {
          mindist = tempdist;
          victim = p2;
        }
      }
    }
  }

  // if the previous loop found a victim (could for example fail,
  // if the idea is already everywhere), it can become part of the idea
  if (total_domination_check) {
    throw std::string("Unusual event: One idea dominates the world.");
  } else {
    // get probability decision about where an idea actually grows
    // dependend on the edge distance value of the victim node
    //if (randunifrange(0, 101) > mindist*100) {
    return(victim);
    //}
  }
}



//void Idea::fight();

Idea* Idea::split(int new_id) {
  // split vertices of currently splitting idea
  std::vector<vertex_desc> v1 = this->vertices;
  std::vector<vertex_desc> v2(
      std::make_move_iterator(v1.begin() + v1.size()/2),
      std::make_move_iterator(v1.end()));
  v1.erase(v1.begin() + v1.size()/2, v1.end());
  // create new idea
  Idea* newidea = new Idea(
    new_id,
    5,
    5,
    10,
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
