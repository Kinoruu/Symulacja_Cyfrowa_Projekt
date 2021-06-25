//#pragma once
#ifndef NETWORK_H
#define NETWORK_H
#include "BaseStation.h"
#include "User.h"
#include "ResourceBlock.h"
#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <vector>
#include "Generators.h"

using namespace std;

class Network
{
public:
  Network(int seed_t, int seed_d, int seed_rk, int seed_tau, int seed_e, double lambda);
  void Init(int);
  void Generateuser(int, string, int, int, int);
  void ResourceAllocation(int, string, int, int, int);
  void Function_block_allocation(User*, size_t, size_t, size_t, int, bool, int, string, int, int);
  void NewPropagation(int, string, int, int, int);
  void Remove(int, string, int, int, int);

  void ser_generate_timer(size_t time) { generate_timer = time; }

  size_t get_buffer_size() { return buffer_.size(); }

  vector<double> get_asbt() { return avg_system_bit_rate_; }
  void set_asbt(vector<double> new_asbt) { avg_system_bit_rate_ = new_asbt; }
  vector<double> get_aubr() { return avg_user_bit_rate_; }
  void set_aubr(vector<double> new_aubr) { avg_user_bit_rate_ = new_aubr; }
  vector<int> get_uat() { return user_awaiting_time_; }
  void set_uat(vector<int> new_uat) { user_awaiting_time_ = new_uat; }
  int get_nous() { return number_of_users_served; }
  int get_nousu() { return number_of_users_served_unstabilized; }
  int get_noe() { return number_of_errors; }
  int get_noeu() { return number_of_errors_unstabilized; }
  int get_nora() { return number_of_resources_allocations; }
  int get_norau() { return number_of_resources_allocations_unstabilized; }
  vector<double> get_hw() { return hist_w; }
  void set_hw(vector<double> new_hw) { hist_w = new_hw; }
  vector<int> get_hr() { return hist_r; }
  void set_hr(vector<int> new_hr) { hist_r = new_hr; }
  vector<bool> get_hzj() { return hist_zj; }
  void set_hw(vector<bool> new_hzj) { hist_zj = new_hzj; }

  double get_lambda() { return lambda; }
  void set_lambda(double new_lambda) { lambda = new_lambda; }

  Generators* generator_t;
  Generators* generator_d;
  Generators* generator_rk;
  Generators* generator_tau;
  Generators* generator_e;

  double lambda;

private:
  ///////////////////////////////////////////////////////////// implementacja list i ich iteratorów
  list<User*> buffer_;
  list<User*>::iterator it;
  list<User*> buffer_temp_;
  ///////////////////////////////////////////////////////////// impplementacja sta³ych systemu
  int generate_timer = -1;
  double probability = 0.1;
  int RB = 25; 
  int l_blocks = 3;
  ///////////////////////////////////////////////////////////// implementacja zmiennych do zbierania statystyk
  vector<double> avg_system_bit_rate_;
  vector<double> avg_user_bit_rate_;
  vector<int> user_awaiting_time_;
  int number_of_users_served = 0;
  int number_of_users_served_unstabilized = 0;
  int number_of_errors = 0;
  int number_of_errors_unstabilized = 0;
  int number_of_resources_allocations = 0;
  int number_of_resources_allocations_unstabilized = 0;
  ///////////////////////////////////////////////////////////// wektory do histogramów 
  vector<int> hist_r;
  vector<double> hist_w;
  vector<bool> hist_zj;
};
#endif