#pragma once

#include <vector>

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

  //! go to the next timestep
  /*!
   Develops the Aether from one timestep to the next. This function controls
   the major developement steps like creation, growth, splitting and death of
   Ideas.
   */
  void develop();
  
  void add_idea_to_mindspace(Idea* new_idea);
  int get_current_graph_size();
  int get_number_of_nodes_in_graph();

  private:
  //! vector that stores references to Idea instances
  std::vector<Idea*> mindspace;
  //! reference to Networkland
  Networkland* realworld;
};
