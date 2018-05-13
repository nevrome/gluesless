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
  
  // Number of iterations
  outfile << "Number of iterations:" << std::endl;
  outfile << this->iteration_count << std::endl << std::endl;
  
  // Number of remaining nodes after this iteration
  outfile << "Number of remaining nodes after this iteration:" << std::endl;
  for (auto& i : this->graph_size_over_time) {
    outfile << i << " ";
  }
  outfile << std::endl << std::endl;
  
  // Nodes per Idea
  outfile << "Nodes per Idea:" << std::endl;
  std::vector<Idea*> all_ideas = overmind->get_mindspace();
  for (auto& p1 : all_ideas) {
    outfile << p1->get_identity() << std::endl;
    std::vector<int> all_nodes_of_idea = p1->get_nodes(); 
    for (auto& p2 : all_nodes_of_idea) {
      outfile << p2 << " ";
    }
    outfile << std::endl;
  }
  outfile << std::endl;
  
  // close connection to file
  outfile.close();
  
}
