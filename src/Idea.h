#pragma once

#include <string>
#include <vector>

#include "Networkland.h"
#include "global_random_generators.h"

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
    std::vector<int> start_nodes
  );

  void live();
  void expand();
  std::vector<int> get_all_neighboring_nodes();
  std::vector<int> select_nodes_to_convert(std::vector<int> neighbors);
  std::vector<int> get_nodes();

  private:
  //! stores identity of an Idea
  std::string identity;
  //! reference to Networkland
  Networkland* realworld;
  //!
  std::vector<int> current_nodes;
  //!
  std::vector<int> dead_nodes;
};
