#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Idea.h"

inline std::vector<Idea*> ideas_file_to_ideas_vector(std::string ideas_file_path) {
  
  std::vector<std::vector<std::string>*>& ideas_file_content = read_delim(ideas_file_path, ";");
  
  for(auto& i : ideas_file_content) {
    std::printf(i->front());
  }
  
}

inline std::vector<std::vector<std::string>*>& read_delim(std::string file_path, char delimiter) {
  
  std::ifstream in(ideas_file_path);
  std::vector<std::vector<std::string>*>& data;
  std::vector<string>* p = NULL;
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

inline void split(const std::string& s, char c, std::vector<string>& v) {
  int i = 0;
  int j = s.find(c);
  while (j >= 0) {
    v.push_back(s.substr(i, i-j));
    i = ++j;
    j = s.find(c, j);
    
    if (j < 0) {
      v.push_back(s.substr(i, s.length()))
    }
  }
}
