#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>

#include "Snap.h"

#include "Timeline.h"

//! main
/*!
  main method
  */
  
int main(int argc, char* argv[]){
  
  // manage input arguments
  TStr pajek_file_path;
  std::string ideas_file_path;
  std::string output_file_path;
  bool quiet = false;

  for (int i = 1; i < argc; i++) {  
    if (strcmp(argv[i], "--pajekfile") == 0 | strcmp(argv[i], "-pi") == 0) {
        pajek_file_path = argv[i + 1];
        i++;
    }
    if (strcmp(argv[i], "--ideasfile") == 0 | strcmp(argv[i], "-ii") == 0) {
        ideas_file_path = argv[i + 1];
        i++;
    }
    if (strcmp(argv[i], "--outputfile") == 0 | strcmp(argv[i], "-o") == 0) {
        output_file_path = argv[i + 1];
        i++;
    }
    if (strcmp(argv[i], "--quiet") == 0 | strcmp(argv[i], "-q") == 0) {
        quiet = true;
    }
  }

  // create world
  Networkland* real = new Networkland(pajek_file_path);
  Aether* overmind = new Aether(real, ideas_file_path);
  Timeline* thyme = new Timeline(overmind);

  // develop
  int graph_size;
  while (true) {
    
    thyme->develop();
    
    int new_graph_size = thyme->get_graph_size_over_time().back();
    if (graph_size == new_graph_size) {
      break;
    }
    graph_size = new_graph_size;
    
    if (!quiet) {
      printf("remaining nodes: ");
      printf(std::to_string(graph_size).c_str());
      printf("      ");
      printf("\r");
      fflush(stdout);
    }
    
  }
  
  // file output
  thyme->export_to_text_file(output_file_path);

  // console output
  if (!quiet) {
    printf("remaining nodes: ");
    printf(std::to_string(thyme->get_graph_size_over_time().back()).c_str());
    printf(" (final)");
    printf("\n");
  }

  // cleaning up 
  delete real;
  delete overmind;
  delete thyme;

  return 0;
}
