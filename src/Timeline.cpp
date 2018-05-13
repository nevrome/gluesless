#include "Timeline.h"
#include <fstream>
#include <iostream>

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

void Timeline::export_to_text_file(std::string file_path) {
  
  // open a file in write mode.
  std::ofstream outfile;
  outfile.open(file_path);
  
  outfile << "Number of iterations:" << std::endl;
  outfile << this->iteration_count << std::endl << std::endl;
  
  outfile << "Number of remaining nodes after this iteration:" << std::endl;
  for (auto& i : this->graph_size_over_time) {
    outfile << i << ";";
  }
  outfile << std::endl << std::endl;
  
  // std::vector<int> cremation_nodes = cremation->get_nodes();
  // std::vector<int> inhumation_nodes = inhumation->get_nodes();
  
  // std::ofstream output_file_cremation("./cremation.txt");
  // std::ostream_iterator<int> output_iterator_cremation(output_file_cremation, "\n");
  // std::copy(cremation_nodes.begin(), cremation_nodes.end(), output_iterator_cremation);
  // std::ofstream output_file_inhumation("./inhumation.txt");
  // std::ostream_iterator<int> output_iterator_inhumation(output_file_inhumation, "\n");
  // std::copy(inhumation_nodes.begin(), inhumation_nodes.end(), output_iterator_inhumation);
  
  outfile.close();
  
}
