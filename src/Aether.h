#ifndef _gluesless_RCPP_Aether_H
#define _gluesless_RCPP_Aether_H

#include <Rcpp.h>
#include <vector>
#include <string>

#include "Idea.h"
#include "Networkland.h"

using namespace Rcpp;

//! Environment, where ideas exist
/*!
 Some kind of ghostworld, where ideas life and interact.
 The status of the Aether can be queried with multiple
 getter functions.
 */

class Aether {

  public:
  Aether(Networkland* real);

  //! get number of ideas
  int get_ideanumber();
  //! get identities of ideas
  /*!
   Returns vector of idea identities of currently present
   ideas.
   */
  vector<int> get_ideas();
  //! get positions of ideas in the Networkland
  /*!
   Returns vector of vector of occupied vertices of
   currently present ideas.
   */
  vector< vector<Vertexdesc> > get_idea_vertices();

  //! go to the next timestep
  /*!
   Develops the Aether from one timestep to the other.
   */
  void develop();

  private:
  std::vector<Idea*> mindspace;
  Networkland* realworld;
};

#endif