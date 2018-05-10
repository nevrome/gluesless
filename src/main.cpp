#include <cstdlib>
#include <math.h>
#include <iostream>

#include "Snap.h"

//#include <progress.hpp>
//#include <progress_bar.hpp>

#include "Idea.h"
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
  Idea* cremation = new Idea("cremation", real, {1,2,3});
  Idea* inhumation = new Idea("inhumation", real, {4,5,6});
  // Idea* flat = new Idea("flat", real);
  // Idea* mound = new Idea("mound", real);
  
  overmind->add_idea_to_mindspace(cremation);
  overmind->add_idea_to_mindspace(inhumation);
  // overmind->add_idea_to_mindspace(flat);
  // overmind->add_idea_to_mindspace(mound);
  
  // develop
  //Progress p(iter, true);
  for (int i = 0; i < 2000; i++) {
    thyme->develop(overmind);
    //if (Progress::check_abort()) {break;}
    //p.increment();
  }
  
  //List res = thyme->export_as_R_list();

  delete real;
  delete overmind;
  delete thyme;
  
  delete cremation;
  delete inhumation;
  // delete flat;
  // delete mound;

  return 0;
}
