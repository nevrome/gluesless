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
    std::string identity,
    Networkland* realworld,
    std::vector<double> power_distribution
  );

  std::string get_identity();
  void set_identity(std::string identity);
  std::map<vertex_desc, double> get_expansion();
  void add_competing_idea(Idea* competing_idea);

  //! It's your turn! Live!
  void live();

  private:
  //! stores identity of an Idea
  std::string identity;
  //! reference to Networkland
  Networkland* realworld;
  //! map that stores vertices and the power of the idea
  std::map<vertex_desc, double> expansion;
  //! exclusive partner ideas that try to fill the same niche
  std::vector<Idea*> competing_ideas;
};
