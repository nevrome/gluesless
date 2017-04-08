#ifndef _gluesless_RCPP_Timeline_H
#define _gluesless_RCPP_Timeline_H

#include <Rcpp.h>
#include <vector>
#include <string>

#include "Aether.h"

using namespace Rcpp;
using namespace std;

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
   development function. Before the development, the
   current status of the Aether is queried and stored.
   */
  void develop(Aether* current);

  private:
  //! stores number of Idea instances over time
  vector<int> ideanumber;
  //! stores Idea identities over time
  vector< vector<int> > ideas;
  //! stores Idea positions over time
  vector< vector< vector<Vertexdesc> > > idea_vertices;
};

#endif