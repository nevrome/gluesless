#pragma once

#include <vector>
#include <string>

#include <Rcpp.h>

#include "Aether.h"

//! Sequence of Aether statuses
/*!
 A Timeline controls and documents the development of
 an Aether and the Ideas within it.
 Every Timeline is linked to an Aether.
 */

class Timeline {

  public:
  Timeline(Aether* start);

  //! export model development
  /*!
   Exports the complete model documentation in a specially
   prepared R list. This object contains data for every
   timestep.
   */
  SEXP export_as_R_list();

  //! go to the next timestep
  /*!
   Jumps from on timestep to the next by calling the Aether
   development function. After the development, the
   current status of the Aether is queried and stored.
   */
  void develop(Aether* current);

  private:
  //! stores number of Idea instances over time
  std::vector<int> ideanumber;
  //! stores Idea identities over time
  std::vector< std::vector<int> > ideas;
  //! stores Idea positions over time
  std::vector< std::vector< std::vector<vertex_desc> > > idea_vertices;
  //! stores Idea fecundities over time
  std::vector< std::vector<int> > fecundities;
  //! stores Idea fidelities over time
  std::vector< std::vector<int> > fidelities;
  //! stores Idea longevities over time
  std::vector< std::vector<int> > longevities;
};
