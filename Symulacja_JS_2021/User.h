//#pragma once
#ifndef USER_H_
#define USER_H_
#include <vector>
#include "ResourceBlock.h"

using namespace std;

// klasa, której obiekty odzwierciedlaj¹ pojedynczego u¿ytkownika
class User //: public ResourceBlock
{
public:
  User(int d, vector<int> rk, double ar, size_t id, int ubn, bool uaf, User *next);
  User* next_ = NULL; // wskaŸnik do sortowania

  size_t get_id() const { return user_id_; }
  size_t get_rk(size_t RB_id) const { return bit_rate_[RB_id]; }
  int get_d() const { return data_size_d_; }
  void set_d(size_t new_d) { data_size_d_ = new_d; }
  int get_ubn() { return user_blocks_number_; }
  void set_ubn(size_t new_ubn) { user_blocks_number_ = new_ubn; }
  void set_rk(vector<int> new_rk) { bit_rate_ = new_rk; }
  double get_ar() { return avg_rk_; }
  void set_ar(double new_ar) { avg_rk_ = new_ar; }
  bool get_uaf() { return user_avg_flag_; }
  void set_uaf(size_t new_uaf) { user_avg_flag_ = new_uaf; }
  size_t get_at() { return arrive_time_; }
  void set_at(size_t new_at) { arrive_time_ = new_at; }
  size_t get_rt() { return remove_time_; }
  void set_rt(size_t new_rt) { remove_time_ = new_rt; }
private:
  
  const size_t user_id_; // unikalny numer u¿ytkownika
  int data_size_d_; // iloœæ danych do odebrania przez u¿ytkownika
  vector<int> bit_rate_; // wektor przep³ywnoœci dla wszystkich bloków
  int user_blocks_number_; // iloœæ bloków przydzielona obecnie u¿ytkownikowi
  vector<ResourceBlock*> user_blocks_; // wektor bloków posiadanych aktualnie przez u¿ytkownika
  double avg_rk_;  // œrednia przep³ywnoœæ obecn¹ przep³ywnoœæ dodajemy gdy u¿ytkownik uzyska³ blok zasobów 
  bool user_avg_flag_; // flaga pomagaj¹ca ustaliæ czy u¿ytkownik mia³ ju¿ policzon¹ œredni¹ w danej pêtli
  int arrive_time_;
  int remove_time_;

};
#endif