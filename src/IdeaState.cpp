#include "IdeaState.h"

IdeaState::IdeaState(
  double power
) {
  this->local_power = power;
}

double IdeaState::get_local_power() { return this->local_power; }
void IdeaState::set_local_power(double power) { this->local_power = power; }
