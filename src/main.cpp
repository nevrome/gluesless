#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>

#include "Snap.h"

//#include <progress.hpp>
//#include <progress_bar.hpp>

//#include "Idea.h"
//#include "Networkland.h"
#include "Timeline.h"

//! main
/*!
  main method
  */
  
int main(int argc, char* argv[]){
  
  // manage input arguments
  const TStr pajek_file_path = argv[1];
  
  // create world
  Networkland* real = new Networkland(pajek_file_path);
  Aether* overmind = new Aether(real);
  Timeline* thyme = new Timeline(overmind);

  

  // create ideas
  Idea* cremation = new Idea("cremation", real, {1});
  Idea* inhumation = new Idea("inhumation", real, {2});
  // Idea* flat = new Idea("flat", real);
  // Idea* mound = new Idea("mound", real);
  
  overmind->add_idea_to_mindspace(cremation);
  overmind->add_idea_to_mindspace(inhumation);
  // overmind->add_idea_to_mindspace(flat);
  // overmind->add_idea_to_mindspace(mound);
  
  // develop
  int graph_size = 0;
  while (true) {
    
    thyme->develop(overmind);
    
    int new_graph_size = real->get_number_of_nodes();
    if (graph_size == new_graph_size) {
      break;
    }
    graph_size = new_graph_size;
    
    printf("remaining nodes: ");
    printf(std::to_string(graph_size).c_str());
    printf("\r");
    fflush(stdout);
    
  }
  
  // file output
  std::vector<int> cremation_nodes = cremation->get_nodes();
  std::vector<int> inhumation_nodes = inhumation->get_nodes();

  std::ofstream output_file_cremation("./cremation.txt");
  std::ostream_iterator<int> output_iterator_cremation(output_file_cremation, "\n");
  std::copy(cremation_nodes.begin(), cremation_nodes.end(), output_iterator_cremation);
  std::ofstream output_file_inhumation("./inhumation.txt");
  std::ostream_iterator<int> output_iterator_inhumation(output_file_inhumation, "\n");
  std::copy(inhumation_nodes.begin(), inhumation_nodes.end(), output_iterator_inhumation);

  // console output
  printf("remaining nodes: ");
  printf(std::to_string(graph_size).c_str());
  printf("\n");
  printf("cremation: ");
  printf(std::to_string(cremation_nodes.size()).c_str());
  printf("\n");
  printf("inhumation: ");
  printf(std::to_string(inhumation_nodes.size()).c_str());
  printf("\n");

  delete real;
  delete overmind;
  delete thyme;
  
  delete cremation;
  delete inhumation;
  // delete flat;
  // delete mound;

  return 0;
}
