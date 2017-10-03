#include "Aether.h"

#include "global.h"

Aether::Aether(Networkland* real, std::vector<vertex_desc> idea_start_pos) {
  this->realworld = real;
  this->idea_id_counter = 0;
  Rcpp::Rcout << "huhu";
  this->initial_idea_start_pos = idea_start_pos;

}

int Aether::get_ideanumber() {
  return this->mindspace.size();
}

std::vector<int> Aether::get_ideas() {
  std::vector<int> res;
  res.reserve(this->mindspace.size());
  for(auto& idx : this->mindspace) {
    res.push_back(idx->get_identity());
  }
  return res;
}

std::vector< std::vector<vertex_desc> > Aether::get_idea_vertices(){
  std::vector< std::vector <vertex_desc> > res;
  res.reserve(this->mindspace.size());
  for(auto& idx : this->mindspace) {
    res.push_back(idx->get_vertices());
  }
  return res;
}

void Aether::develop() {

  auto& v = this->mindspace;

  // if no ideas are present, create one (simulation startup)
  if(v.size() == 0){
    Idea* newidea = new Idea(this->idea_id_counter, realworld, this->initial_idea_start_pos);
    // increase Aether id counter
    this->idea_id_counter++;
    // store new idea in mindspace
    v.push_back(newidea);
  }

  // create offset vector
  std::vector<int> offset;
  offset.reserve(v.size());
  for (size_t i=0u; i<v.size(); ++i) {
    offset.push_back(i);
  }
  random_shuffle(
    offset.begin(),
    offset.end(),
    randWrapper
  );

  // iterate over the ideas effectively shuffled by the
  // offset
  for (auto& idx : offset) {
    auto it = v.begin() + idx;
    //infect
    (*it)->infect();
  }


}
