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
    for(auto it = em.begin(); it != em.end(); it++) {
      //Rcpp::Rcout << realworld->get_name(it->first) << std::endl;
      rm.push_back(realworld->get_name(it->first));
    }
    res.push_back(rm);
  }
  return res;
}

std::vector< std::vector< double > > Aether::get_idea_powers(){
  std::vector< std::vector< double > > res;
  res.reserve(this->mindspace.size());
  for (auto& idx : this->mindspace) {
    auto em = idx->get_expansion();
    std::vector<double> ip;
    for(auto it = em.begin(); it != em.end(); it++) {
      ip.push_back(it->second->get_local_power());
    }
    res.push_back(ip);
  }
  return res;
}

std::vector< std::vector< double > > Aether::get_idea_poison_amounts(){
  std::vector< std::vector< double > > res;
  res.reserve(this->mindspace.size());
  for (auto& idx : this->mindspace) {
    auto em = idx->get_expansion();
    std::vector<double> ip;
    for (auto it = em.begin(); it != em.end(); it++) {
      ip.push_back(it->second->get_local_poison_amount());
    }
    res.push_back(ip);
  }
  return res;
}

void Aether::develop() {

  auto& v = this->mindspace;

  // create offset vector to shuffle idea order
  std::vector<int> offset;
  offset.reserve(v.size());
  for (size_t i = 0u; i < v.size(); ++i) {
    offset.push_back(i);
  }
  random_shuffle(
    offset.begin(),
    offset.end(),
    randWrapper
  );

  for (auto& idx : offset) {
    auto current_idea = v.begin() + idx;
    (*current_idea)->live();
  }

}
