#pragma once

#include <string>
#include <vector>

#include "Networkland.h"
#include "IdeaState.h"

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
  std::map<vertex_desc, IdeaState*> get_expansion();
  void set_expansion(std::vector<double> power_distribution);
  void add_competing_idea(Idea* competing_idea);
  //IdeaState* get_ideastate_at_vertex()

  void live();
  void produce_poison();
  void try_to_grow_with_poison();
  void colonize_random_region();
  IdeaState* get_state_competing_idea(vertex_desc region);


  private:
  //! stores identity of an Idea
  std::string identity;
  //! reference to Networkland
  Networkland* realworld;
  //! map that stores vertices and the state of the idea at the vertices
  std::map<vertex_desc, IdeaState*> expansion;
  //! exclusive partner ideas that try to fill the same niche
  std::vector<Idea*> competing_ideas;
};
