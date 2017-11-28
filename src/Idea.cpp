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
  // fill expansion map
  std::pair<vertex_iter, vertex_iter> vp;
  double it = 0;
  for (vp = realworld->get_all_vertices(); vp.first != vp.second; ++vp.first) {
    expansion.insert(std::pair<vertex_desc, double>(*vp.first, power_distribution[0]));
    it++;
  }
}

std::string Idea::get_identity() { return this->identity; }
void Idea::set_identity(std::string identity) { this->identity = identity; }
std::map<vertex_desc, double> Idea::get_expansion() { return this->expansion;}

void Idea::live() {
  // TODO
}
