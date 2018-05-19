#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Idea.h"

inline void split(const std::string& s, char c, std::vector<std::string>& v) {
  int i = 0;
  int j = s.find(c);
  while (j >= 0) {
    v.push_back(s.substr(i, j-i));
    i = ++j;
    j = s.find(c, j);
    
    if (j < 0) {
      v.push_back(s.substr(i, s.length()));
    }
  }
}

inline void read_delim(std::string file_path, std::vector<std::vector<std::string>*>& data, char delimiter) {
  
  std::ifstream in(file_path);
  std::vector<std::string>* p = NULL;
  std::string tmp;
  
  while (!in.eof()) {
    std::getline(in, tmp, '\n');
    
    p = new std::vector<std::string>();
    split(tmp, delimiter, *p);
    
    data.push_back(p);

    std::cout << tmp << '\n';
    tmp.clear();
  }
  
}

inline std::vector<Idea*> ideas_file_to_ideas_vector(std::string ideas_file_path, Networkland* real) {
  
  std::vector<std::vector<std::string>*> data;
  
  read_delim(ideas_file_path, data, ',');
  
  std::vector<Idea*> mindspace;
  for(auto& p : data) {
    // Idea* new_idea = new Idea(p1.front(), real, {2});
    // mindspace.push_back(new_idea);
    std::cout << p->front() << std::endl;
  }
  
  return(mindspace);
}


