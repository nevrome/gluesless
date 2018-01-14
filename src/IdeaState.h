#pragma once

#include <Rcpp.h>

class IdeaState {

  public:
  IdeaState(
    double local_power
  );

  double get_local_power();
  void set_local_power(double power);
  double get_local_poison_amount();
  void set_local_poison_amount(double poison_amount);

  void produce_poison_local();
  void determine_poison_production();

  private:
  double local_power;
  double local_poison_amount;
  double local_poison_production;

};
