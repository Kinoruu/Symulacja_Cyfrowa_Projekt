//#pragma once
#ifndef SIMULATOR_H_
#define SIMULATOR_H_
#include "Network.h"
#include <string>
#include "Generators.h"


class Simulator
{
public:
  explicit Simulator(Network* network);
  void Simulation(int time, int tryb, int view, int initial_phase, int end, int max_user_served, double lambda);
  
  double get_l() { return lambda; }
  void set_l(double new_l) { lambda = new_l; }

private:
  size_t allocation_time = 5;
  size_t clock_ = 0;
  Network* network_ = nullptr;
  string c_clock;
  double lambda_tau = 0.1;
  double lambda ;
};
#endif