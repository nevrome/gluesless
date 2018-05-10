#include "Aether.h"
#include "global.h"

Aether::Aether(Networkland* real) {
  this->realworld = real;
}

void Aether::develop() {

}

void Aether::add_idea_to_mindspace(Idea* new_idea) {
  this->mindspace.push_back(new_idea);
}
