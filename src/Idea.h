#pragma once

#include <string>
#include <vector>

#include <Rcpp.h>

#include "Networkland.h"

//! Idea/Innovation - ABM agent
/*!
 An Idea is a simple representation of a human idea or
 innovation. It lifes in an Aether, mutates and
 interacts with other ideas and a Networkland.
 */

class Idea {

  public:
  Idea(
    int id,
    int pow,
    int fec,
    int fid,
    int lon,
    Networkland* real,
    std::vector<vertex_desc> birth_vertices
  );

  //! get identity of an Idea
  /*!
   Returns identity of an Idea.
   */
  int get_identity();
  void set_identity(int id);
  bool is_alive();
  void die();
  int get_power();
  int get_fecundity();
  int get_fidelity();
  int get_longevity();
  int get_age();

  //! get positions of an Idea
  /*!
   Returns vector of vertices that are occupied by an Idea.
   */
  std::vector<vertex_desc> get_vertices();

  //! Interaction between Idea and Networkland
  /*!
   An Idea occupies other vertices in the Networland.
   */
  vertex_desc direction_selection();
  void infect(vertex_desc victim_hex);
  void fight(Idea* enemy, vertex_desc victim_hex);

  //! An Idea grows older
  void age();

  // An Idea splits into two ideas at the end of its life
  Idea* split(int new_id);


  private:
  //! stores identity of an Idea
  int identity;
  //! is the idea alive?
  bool alive = true;
  //! power value -- Überzeugungskraft
  //! Ideas with high power value win fights. Because they are the better ideas.
  //! Per definition.
  int power;
  //! fecundity value -- Fruchtbarkeit -- determines, how many
  //! nodes an idea can infect in one timestep
  int fecundity;
  //! fidelity value -- Wiedergabetreue -- determines how stable an idea is
  int fidelity;
  //! longevity value -- Langlebigkeit -- determines, how many
  //! timesteps an idea lives
  int longevity;
  //! age value -- how many timesteps did an idea already live?
  int age_in_timesteps;
  //! reference to Networkland
  Networkland* realworld;
  //! vector that stores vertices occupied by an Idea
  std::vector<vertex_desc> vertices;
};
