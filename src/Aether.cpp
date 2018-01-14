#include <math.h>

#include "Aether.h"
#include "global.h"

Aether::Aether(Networkland* real) {
  this->realworld = real;
}

size_t Aether::get_size_of_mindspace() {return this->mindspace.size();}

Idea* Aether::get_idea_from_mindspace(size_t index) {return this->mindspace.at(index);}

void Aether::add_idea_to_mindspace(Idea* new_idea) {
  this->mindspace.push_back(new_idea);
}

std::vector<std::string> Aether::get_ideas() {
  std::vector<std::string> res;
  res.reserve(this->mindspace.size());
  for (auto& idx : this->mindspace) {
    res.push_back(idx->get_identity());
  }
  return res;
}

std::vector< std::vector< std::string > > Aether::get_idea_regions(){
  std::vector< std::vector< std::string > > res;
  res.reserve(this->mindspace.size());
  for (auto& idx : this->mindspace) {
    auto em = idx->get_expansion();
    std::vector<std::string> rm;
    for(auto it = em.begin(); it != em.end(); ++it) {
      //Rcpp::Rcout << realworld->get_region_name(it->first) << std::endl;
      rm.push_back(realworld->get_region_name(it->first));
    }
    res.push_back(rm);
  }
  return res;
}

std::vector< std::vector< double > > Aether::get_idea_parts(){
  std::vector< std::vector< double > > res;
  res.reserve(this->mindspace.size());
  for (auto& idx : this->mindspace) {
    auto em = idx->get_expansion();
    std::vector<double> ip;
    for(auto it = em.begin(); it != em.end(); ++it) {
      ip.push_back(it->second);
    }
    res.push_back(ip);
  }
  return res;
}

void Aether::develop() {

  // create convenient short
  auto& v = this->mindspace;

  for (auto& idx : v) {
    idx->live();
  }


}
