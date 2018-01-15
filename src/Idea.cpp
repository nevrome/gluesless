#include "Idea.h"

#include <algorithm>

#include "global.h"

Idea::Idea(
  std::string identity,
  Networkland* realworld,
  std::vector<double> power_distribution
) {
  this->identity = identity;
  this->realworld = realworld;
  set_expansion(power_distribution);
}

std::string Idea::get_identity() { return this->identity; }
void Idea::set_identity(std::string identity) { this->identity = identity; }
std::map<vertex_desc, IdeaState*> Idea::get_expansion() { return this->expansion;}
void Idea::set_expansion(std::vector<double> power_distribution) {
  std::pair<vertex_iter, vertex_iter> vp;
  size_t it = 0;
  for (vp = this->realworld->get_all_vertices(); vp.first != vp.second; vp.first++) {
    IdeaState* state_for_one_region = new IdeaState(power_distribution[it]);
    expansion.insert(std::pair<vertex_desc, IdeaState*>(*vp.first, state_for_one_region));
    it++;
  }
}
void Idea::add_competing_idea(Idea* competing_idea) {
  this->competing_ideas.push_back(competing_idea);
}

void Idea::live() {
  this->produce_poison();
  this->try_to_grow_with_poison();
  this->colonize_random_region();
}

void Idea::produce_poison() {
  for (auto it = this->expansion.begin(); it != this->expansion.end(); it++) {
    it->second->produce_poison_local();
  }
}

void Idea::try_to_grow_with_poison() {
  // loop to go through all regions
  for(auto it = this->expansion.begin(); it != this->expansion.end(); it++) {
    auto state_idea = it->second;

    if (state_idea->is_local_poison_amount_above_quorum(1.0)) {
      double growth = (1.0 - state_idea->get_local_power()) / 50.0;
      state_idea->change_power_poison_related(growth);
      auto state_competing_idea = get_state_competing_idea(it->first);
      state_competing_idea->change_power_poison_related(-growth);

      state_idea->set_poison_zero();
    }
  }
}

void Idea::colonize_random_region() {

  for(auto it = this->expansion.begin(); it != this->expansion.end(); it++) {
    auto state_idea = it->second;

    if (randunifrange(0, 100) < 5) {
      double growth = (1.0 - state_idea->get_local_power()) / 10.0;
      state_idea->change_local_power(growth);
      auto state_competing_idea = get_state_competing_idea(it->first);
      state_competing_idea->set_local_power(1.0 - state_idea->get_local_power());
    }
  }

}

IdeaState* Idea::get_state_competing_idea(vertex_desc region) {
  return this->competing_ideas.front()->expansion.find(region)->second;
}
