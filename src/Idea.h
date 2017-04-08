#ifndef _gluesless_RCPP_Idea_H
#define _gluesless_RCPP_Idea_H

#include <Rcpp.h>
#include <string>
#include <vector>

#include "Networkland.h"

using namespace Rcpp;
using namespace std;

//! Idea/Innovation - ABM agent
/*!
 An Idea is a simple representation of a human idea or
 innovation. It lifes in an Aether, mutates and
 interacts with other ideas and a Networkland.
 */

class Idea {

  public:
  Idea(Networkland* space);

  //! get identity of an Idea
  /*!
   Returns identity of an Idea.
   */
  int get_identity();
  //string get_identity();

  //! get positions of an Idea
  /*!
   Returns vector of vertices that are occupied by an Idea.
   */
  vector<Vertexdesc> get_vertices();

  //! Interaction between Idea an Networkland
  /*!
   An Idea occupies other vertices in the Networland.
   */
  void infect();
  // mutate();
  // conjugate();


  private:
  //! stores identity of an Idea
  int identity;
  //string identity;
  //! reference to Networkland
  Networkland* realworld;
  //! vector that stores vertices occupied by an Idea
  vector<Vertexdesc> vertices;
};

std::string create_random_string(size_t length);
size_t compare_strings(
    const std::string &s1,
    const std::string &s2
  );
size_t compare_ideas(Idea* a, Idea* b);

#endif