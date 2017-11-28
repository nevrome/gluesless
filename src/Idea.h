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

  //! get/set identity of an Idea
  std::string get_identity();
  void set_identity(std::string identity);
  //! get expansion map of an Idea
  std::map<vertex_desc, double> get_expansion();

  //! It's your turn! Live!
  void live();

  private:
  //! stores identity of an Idea
  std::string identity;
  //! reference to Networkland
  Networkland* realworld;
  //! map that stores vertices and the power of the idea
  std::map<vertex_desc, double> expansion;
};
