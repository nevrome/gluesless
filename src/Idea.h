#pragma once

#include <string>
#include <vector>

#include <Rcpp.h>

#include "Networkland.h"

//! Idea/Innovation/Meme/Memeplex - ABM agent
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
  int get_identity();
  //! set identity of an Idea
  void set_identity(int id);
  //! check if an Idea is alive
  bool is_alive();
  //! get power of an Idea
  int get_power();
  //! get fecundity of an Idea
  int get_fecundity();
  //! get fidelity of an Idea
  int get_fidelity();
  //! get longevity of an Idea
  int get_longevity();
  //! get positions of an Idea
  /*!
   Returns vector of vertices that are occupied by an Idea.
   */
  std::vector<vertex_desc> get_vertices();
  //! get age of an Idea
  int get_age();

  //! set age of an Idea to 0
  void set_age_back();
  //! increase the age of an Idea by 1
  void age();

  //! make selection which Vertex an Idea should occupy/attack next
  /*!
   TODO: ...
   */
  vertex_desc direction_selection();
  //! Idea occupies a Vertex which is empty or still has space
  /*!
   TODO: ...
   */
  void infect(vertex_desc victim_hex);
  //! Idea fights against an other Idea to occupy an already completely occupied Vertex
  /*!
   TODO: ...
   */
  void fight(Idea* enemy, vertex_desc victim_hex);
  //! an Idea splits into two ideas at the end of its life
  /*!
   TODO: ...
   */
  Idea* split(int new_id);
  //! Kill an idea
  /*!
   Sets alive flag of the Idea to false, cleans Idea out of Vertizes of the
   Networkland and empties Vertex vector of Idea.
   */
  void die();

  private:
  //! stores identity of an Idea
  int identity;
  //! is the Idea alive?
  bool alive = true;
  //! power value -- Überzeugungskraft
  /*!
   Ideas with high power value win fights. Because they are the better ideas.
   Per definition.
   */
  int power;
  //! fecundity value -- Fruchtbarkeit
  /*!
   Determines, how many nodes an idea can infect in one timestep.
   */
  int fecundity;
  //! fidelity value -- Wiedergabetreue
  /*!
   Determines, if an idea is nomal enough to split. Whoever deviates to much
   from the norm can't split any more.
   */
  int fidelity;
  //! longevity value -- Langlebigkeit
  /*!
   Determines, how many timesteps an idea lives.
   */
  int longevity;
  //! how many timesteps did an idea already live?
  int age_in_timesteps;
  //! reference to Networkland
  Networkland* realworld;
  //! vector that stores vertices occupied by an Idea
  std::vector<vertex_desc> vertices;
};
