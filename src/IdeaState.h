#pragma once

#include <Rcpp.h>

class IdeaState {

  public:
  IdeaState(
    double local_power
  );

  double get_local_power();
  void set_local_power(double power);
  size_t get_local_poison_amount();
  void set_local_poison_amount(size_t poison_amount);
  size_t get_local_poison_production();
  void set_local_poison_production(size_t poison_production);

  void produce_poison_local();

  private:
  double local_power;
  size_t local_poison_amount;
  size_t local_poison_production;

};
