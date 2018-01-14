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
  void change_local_power(double value);
  bool is_local_poison_amount_above_quorum();
  void set_poison_zero();

  private:
  double local_power;
  double local_poison_amount;
  double local_poison_production;

};
