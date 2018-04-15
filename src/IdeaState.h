#pragma once

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
  bool is_local_poison_amount_above_quorum(double quorum);
  void set_poison_zero();
  bool is_local_power_above_zero_and_below_one();
  void change_power_poison_related(double value);

  private:
  double local_power;
  double local_poison_amount;
  double local_poison_production;

};
