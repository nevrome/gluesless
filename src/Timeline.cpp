#include "Timeline.h"

Timeline::Timeline(Aether* overmind) {
  this->overmind = overmind;
  this->iteration_count = 0;
  this->graph_size_over_time.push_back(this->overmind->get_number_of_nodes_in_graph());
}

void Timeline::develop() {

  // develop Aether
  this->overmind->develop();
  
  // store information for every time step
  this->iteration_count += 1;
  this->graph_size_over_time.push_back(this->overmind->get_number_of_nodes_in_graph());
   
}

int Timeline::get_iteration_count() {
  return(this->iteration_count);
}

std::vector<int> Timeline::get_graph_size_over_time() {
  return(this->graph_size_over_time);
}

void Timeline::export_to_text_file() {
}
