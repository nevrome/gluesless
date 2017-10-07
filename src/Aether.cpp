#include "Aether.h"

#include "global.h"

Aether::Aether(Networkland* real, std::vector<vertex_desc> idea_start_pos) {
  this->realworld = real;
  this->idea_id_counter = 0;
  this->initial_idea_start_pos = idea_start_pos;

}

int Aether::get_idea_id_counter() {
  return this->idea_id_counter;
}

void Aether::increment_idea_id_counter() {
  this->idea_id_counter++;
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

  // if no ideas are present, create the first one (simulation startup)
  if(v.size() == 0){
    Idea* newidea = new Idea(
      this->idea_id_counter,
      5,
      5,
      10,
      realworld,
      this->initial_idea_start_pos
    );
    // increase Aether id counter
    this->increment_idea_id_counter();
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
    // check if the idea dies of old age
    if ((*it)->get_age() == (*it)->get_longevity()) {
      // if yes: the idea splits
      Idea* newidea = (*it)->split(this->idea_id_counter);
      this->increment_idea_id_counter();
      v.push_back(newidea);
    } else {
      // if no: the idea grows and ages
      (*it)->grow();
      (*it)->age();
    }
  }


}
