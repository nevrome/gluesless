#pragma once

#include <vector>
#include <string>

#include "Aether.h"

//! Sequence of Aether statuses
/*!
 A Timeline controls and documents the development of
 an Aether and the Ideas within it.
 Every Timeline is linked to an Aether.
 */

class Timeline {

  public:
  Timeline(Aether* overmind);

  //! go to the next timestep
  /*!
   Jumps from on timestep to the next by calling the Aether
   development function. After the development, the
   current status of the Aether is queried and stored.
   */
  void develop();

  int get_iteration_count();
  std::vector<int> get_graph_size_over_time();

  //! export model development
  /*!
   Exports the complete model documentation in a specially
   prepared text file. This file contains data for every
   timestep.
   */
  void export_to_text_file(std::string file_path);
  
private:
  Aether* overmind;
  int iteration_count;
  std::vector<int> graph_size_over_time;
  
};
