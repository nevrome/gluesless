#include "IdeaState.h"

IdeaState::IdeaState(
  double power
) {
  this->local_power = power;
}

double IdeaState::get_local_power() { return this->local_power; }
void IdeaState::set_local_power(double power) { this->local_power = power; }
size_t IdeaState::get_local_poison_amount() {
  return this->local_poison_amount;
}
void IdeaState::set_local_poison_amount(size_t poison_amount) {
  this->local_poison_amount = poison_amount;
}
size_t IdeaState::get_local_poison_production() {
  return this->local_poison_production;
}
void IdeaState::set_local_poison_production(size_t poison_production) {
  this->local_poison_production = poison_production;
}

void IdeaState::produce_poison_local() {
  this->local_poison_amount += this->local_poison_production;
}
