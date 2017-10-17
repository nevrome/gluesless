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
  Aether(Networkland* real, std::vector<vertex_desc> idea_start_pos);

  int get_idea_id_counter();
  void increment_idea_id_counter();

  //! get number of ideas
  int get_ideanumber();
  //! get identities of Idea instances
  /*!
   Returns vector of identities of currently present
   Idea instances.
   */
  std::vector<int> get_ideas();
  //! get positions of Idea instances in the Networkland
  /*!
   Returns vector of vector of occupied vertices of
   currently present Idea instances.
   */
  std::vector< std::vector<vertex_desc> > get_idea_vertices();
  //! get fecundities of Idea instances
  std::vector<int> get_fecundities();
  //! get fidelities of Idea instances
  std::vector<int> get_fidelities();
  //! get longevities of Idea instances
  std::vector<int> get_longevities();


  //! go to the next timestep
  /*!
   Develops the Aether from one timestep to the other.
   */
  void develop();

  private:
  //! idea identity counter
  int idea_id_counter;
  //! staring positions of initial idea
  std::vector<vertex_desc> initial_idea_start_pos;
  //! vector that stores references to Idea instances
  std::vector<Idea*> mindspace;
  //! reference to Networkland
  Networkland* realworld;
};
