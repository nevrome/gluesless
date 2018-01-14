#pragma once

class IdeaState {

  public:
  IdeaState(
    double local_power
  );

  double get_local_power();
  void set_local_power(double power);

  private:
  double local_power;

};
