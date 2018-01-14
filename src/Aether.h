#pragma once

#include <vector>
#include <string>

#include <Rcpp.h>

#include "Idea.h"
#include "Networkland.h"

//! World where Idea instances exist
/*!
  An Aether is a world, where Idea instances life and
  interact. The status of an Aether can be queried with
  multiple getter functions.
  Every Aether is linked to a Networkland.
  */

class Aether {

  public:
  Aether(Networkland* real);

  size_t get_size_of_mindspace();
  Idea* get_idea_from_mindspace(size_t index);
  void add_idea_to_mindspace(Idea* new_idea);
  //! get identities of Idea instances
  /*!
   Returns vector of names of currently present
   Idea instances.
   */
  std::vector<std::string> get_ideas();
  //! get expansions of Idea instances in the Networkland
  /*!
   Returns vector of maps of occupied vertices and power distributions
   */
  std::vector< std::vector< std::string > > get_idea_regions();

  std::vector< std::vector< double > > get_idea_parts();

  //! go to the next timestep
  /*!
   Develops the Aether from one timestep to the next. This function controls
   the major developement steps like creation, growth, splitting and death of
   Ideas.
   */
  void develop();

  private:
  //! vector that stores references to Idea instances
  std::vector<Idea*> mindspace;
  //! reference to Networkland
  Networkland* realworld;
};
