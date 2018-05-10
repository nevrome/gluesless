#include "Idea.h"

Idea::Idea(
  std::string identity,
  Networkland* realworld
) {
  this->identity = identity;
  this->realworld = realworld;
}

void Idea::live() {
  printf("hu");
}