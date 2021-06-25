#include "Network.h"
#include "User.h"
#include "Event.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <list>
#include "Generators.h"

Network::Network(int seed_t, int seed_d, int seed_rk, int seed_tau, int seed_e, double lambda)
{
  generator_t = new Generators(seed_t);
  generator_d = new Generators(seed_d);
  generator_rk = new Generators(seed_rk);
  generator_tau = new Generators(seed_tau);
  generator_e = new Generators(seed_e);
  set_lambda(lambda);
}

void Network::Init(int sim_time)
{
  while (!buffer_.empty())
  { buffer_.pop_front(); }
  vector<double> avg_system_bit_rate_temp (10);
  generate_timer = -1;
}

void Network::Generateuser(int view, string c_clock, int ms, int time, int initial_phase)
{
  static size_t id = 0;
  ++id;
  int d = 250 * generator_d->Rand(1, 10);
  //hist_r.push_back(d);
  vector<int> rk;
  for (int i = 0; i < RB; i++) { rk.push_back(generator_rk->Rand(20, 800)); hist_r.push_back(rk[i]); }
  int ubn = 0;
  size_t ar = 0;
  bool uaf = 0;
  User *next = NULL;
  auto user = new User(d, rk, ar, id, ubn, uaf, next);
  buffer_.push_back(user);
  user->set_at(ms);
  int cy = 0;
  if (user->get_d() < 1000) { ++cy; }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
  if ((user->get_id() > 9999) && ((view == 1) || (view == 2))) cout << c_clock << " [info]  " << "Generated User id " << user->get_id() << string(26, ' ') << " || data left to receive " << user->get_d() << string(cy, ' ') << " b" << "\n";
  else if ((user->get_id() > 999) && ((view == 1) || (view == 2))) cout << c_clock << " [info]  " << "Generated User id " << user->get_id() << string(27, ' ') << " || data left to receive " << user->get_d() << string(cy, ' ') << " b" << "\n";
  else if ((user->get_id() > 99) && ((view == 1) || (view == 2))) cout << c_clock << " [info]  " << "Generated User id " << user->get_id() << string(28, ' ') << " || data left to receive " << user->get_d() << string(cy, ' ') << " b" << "\n";
  else if (user->get_id() > 9 && ((view == 1) || (view == 2))) cout << c_clock << " [info]  " << "Generated User id " << user->get_id() << string(29, ' ') << " || data left to receive " << user->get_d() << string(cy, ' ') << " b" << "\n";
  else if ((view == 1) || (view == 2))cout << c_clock << " [info]  " << "Generated User id " << user->get_id() << string(30, ' ') << " || data left to receive " << user->get_d() << string(cy, ' ') << " b" << "\n";
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void Network::Remove(int view, string c_clock, int ms, int initial_phase, int time)
{
  for (auto it : buffer_)  // pêtla usuwaj¹ca u¿ytkowników
  { 
    if (it->get_d() == 0)
    {
      it->set_rt(time);
      int awaiting_time = 0;
      awaiting_time = ms - it->get_at();
      int ci = 1;
      if (it->get_id() < 1000) { ++ci; }
      if (it->get_id() < 100) { ++ci; }
      if (it->get_id() < 10) { ++ci; }
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
      if ((view == 1) || (view == 7)) cout << c_clock << " [info]  " << "User id " << it->get_id() << string(ci, ' ') <<" has been removed from system after " << awaiting_time <<  "\n";
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
      ++number_of_users_served_unstabilized;
      if (ms >= initial_phase)
      {
        int id = it->get_id();
        user_awaiting_time_.push_back(awaiting_time);
        double x = it->get_ar();
        avg_user_bit_rate_.push_back(x);
        ++number_of_users_served;
      }
    }
  }
  buffer_temp_.clear();
  for (auto& it : buffer_)  // pêtla usuwaj¹ca u¿ytkowników
  {
    if (it->get_d() != 0)
    {
      buffer_temp_.push_back(it);
    }
  }
  buffer_ = buffer_temp_;
}

void Network::ResourceAllocation(int view, string c_clock, int ms, int time, int initial_phase)
{
  avg_system_bit_rate_.resize(ms + 5);
  for (auto const& it : buffer_)
  {
    int ubn = 0;
    it->set_ubn(ubn);
  }
  Remove(view, c_clock, ms, initial_phase, time);
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
  if ((view == 1) || (view == 8)) cout << c_clock << " [info]  " << "Number of Users in the system " << get_buffer_size() << "\n";
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
  for (int i = 0; i < RB; i++)
  {
    buffer_.sort();
    size_t RB_id = i;
    size_t u_id;
    bool e;
    e = generator_e->RandZeroOne(probability);
    //hist_zj.push_back(e);
    size_t rk = 0;
    bool iter_l = false;
    User* found = nullptr;
    for (auto const& it : buffer_)   // pêtla poszukuj¹ca zgodnie z algorytmem u¿ytkownika dla danego bloku zasobów
    {
      if ((iter_l == false) && (it->get_d() > 0) && (it->get_ubn() < l_blocks))
      {
        found = it;
        iter_l = true;
      }
      else
      {
        if (found)
        {
          if ((it->get_rk(i) == found->get_rk(i)) && (it->get_d() > 0) && (it->get_ubn() < l_blocks) && (found != nullptr))
          {
            if ((it->get_ar() < found->get_ar()) && (it->get_d() > 0) && (it->get_ubn() < l_blocks) && (found != nullptr)) found = it;
          }
          else if ((it->get_rk(i) > found->get_rk(i)) && (it->get_d() > 0) && (it->get_ubn() < l_blocks) && (found != nullptr)) found = it;
        }
      }
    }

    if (found != nullptr) // warunek przydzia³u zasobów
    {
      int ubn = found->get_ubn();
      u_id = found->get_id();
      Function_block_allocation(found, u_id, RB_id, rk, ubn, e, view, c_clock, ms, initial_phase);
      double ar = found->get_ar();
      rk = found->get_rk(RB_id);
      ar = (ar + rk) / 2;
      found->set_ar(ar);
      found->set_uaf(1);
    }

    for (auto const& it : buffer_)  // pêtla uzupe³niaj¹ca œredni¹ przep³ywnoœæ
    {
      if (it->get_uaf() != true)
      {
        double ar = it->get_ar();
        rk = 0;
        ar = (ar + rk) / 2;
        it->set_ar(ar);
      }
    }
  }
}

void Network::Function_block_allocation(User* it, size_t u_id, size_t RB_id, size_t rk, int ubn, bool e, int view, string c_clock, int ms, int initial_phase)
{
  ++ubn;
  it->set_ubn(ubn);
  rk = it->get_rk(RB_id);
  ++number_of_resources_allocations_unstabilized;
  if (ms >= initial_phase) { ++number_of_resources_allocations; }
  if (e == 0)          // zdarzenie warunkowe - sprawdzenie czy potrzeban bêdzie "retransmisja"
  {
    size_t data = it->get_d();
    size_t data_to_be_sent = 0;
    for (int i = 0; i < 5; i++)
    {
      if (data == 0) {}
      if ((rk) > data) 
      { 
        data_to_be_sent += data;
        data = 0; 
        if (ms >= initial_phase)
        {
          if ((avg_system_bit_rate_[ms - 1] == 0) || (ms - 1 > avg_system_bit_rate_.size())) { avg_system_bit_rate_[ms - 1] = rk; }
          else avg_system_bit_rate_[ms - 1] = (avg_system_bit_rate_[ms - 1] + rk) / 2;
        }
      }
      else if(rk < data)
      { 
        data_to_be_sent += rk;
        data -= rk; 
        if (ms >= initial_phase)
        {
          if ((avg_system_bit_rate_[ms - 1] == 0) || (ms - 1 > avg_system_bit_rate_.size())) { avg_system_bit_rate_[ms - 1] = rk; }
          else avg_system_bit_rate_[ms - 1] = (avg_system_bit_rate_[ms - 1] + rk) / 2;
        }
      }
      ++ms;
    }
    it->set_d(data);
    size_t show_d = it->get_d();
    int cn = 5;
    if (RB_id + 1 > 9) { --cn; }
    int cm = 1;
    int cz = 0;
    if (data_to_be_sent < 1000) { ++cz; }
    if (data_to_be_sent < 100) { ++cz; }
    if (data_to_be_sent < 10) { ++cz; }
    int cy = 0;
    if (show_d < 1000) { ++cy; }
    if (show_d < 100) { ++cy; }
    if (show_d < 10) { ++cy; }
    int cr = 3;
    //if (rk > 99) { --cr; }
    int ck = 1;
    if (rk < 100) { ++ck; }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    if ((u_id > 9999) && ((view == 1) || (view == 3))) cout << c_clock << " [info]  " << "Resource Block " << RB_id + 1 << string(cn, ' ') << " || allocated to user " << u_id << string(1, ' ') << " || data sent " << data_to_be_sent << string(cz, ' ') << " b" << string(cm, ' ') << " with bit rate " << rk << string(ck, ' ') << "kb/s " << string(cr, ' ') << " || data left to receive " << show_d << string(cy, ' ') << " b" << "\n";
    else if ((u_id > 999) && ((view == 1) || (view == 3))) cout << c_clock << " [info]  " << "Resource Block " << RB_id + 1 << string(cn, ' ') << " || allocated to user " << u_id << string(2, ' ') << " || data sent " << data_to_be_sent << string(cz, ' ') << " b" << string(cm, ' ') << " with bit rate " << rk << string(ck, ' ') << "kb/s " << string(cr, ' ') << " || data left to receive " << show_d << string(cy, ' ') << " b" << "\n";
    else if ((u_id > 99) && ((view == 1) || (view == 3))) cout << c_clock << " [info]  " << "Resource Block " << RB_id + 1 << string(cn, ' ') << " || allocated to user " << u_id << string(3, ' ') << " || data sent " << data_to_be_sent << string(cz, ' ') << " b" << string(cm, ' ') << " with bit rate " << rk << string(ck, ' ') << "kb/s " << string(cr, ' ') << " || data left to receive " << show_d << string(cy, ' ') << " b" << "\n";
    else if ((u_id > 9) && ((view == 1) || (view == 3))) cout << c_clock << " [info]  " << "Resource Block " << RB_id + 1 << string(cn, ' ') << " || allocated to user " << u_id << string(4, ' ') << " || data sent " << data_to_be_sent << string(cz, ' ') << " b" << string(cm, ' ') << " with bit rate " << rk << string(ck, ' ') << "kb/s " << string(cr, ' ') << " || data left to receive " << show_d << string(cy, ' ') << " b" << "\n";
    else if ((view == 1) || (view == 3)) cout << c_clock << " [info]  " << "Resource Block " << RB_id + 1 << string(cn, ' ') << " || allocated to user " << u_id << string(5, ' ') << " || data sent " << data_to_be_sent << string(cz, ' ') << " b" << string(cm, ' ') << " with bit rate " << rk << string(ck, ' ') << "kb/s " << string(cr, ' ') << " || data left to receive " << show_d << string(cy, ' ') << " b" << "\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
  }
  else   // zajœcie zdarzenia warunkowego "retransmisja" czyli w tym momencie u¿ytkownik odbiera 0 bitów
  {
    ++number_of_errors_unstabilized;
    if (ms >= initial_phase) { ++number_of_errors; }
    size_t show_d = it->get_d();
    int cn = 5;
    if (RB_id + 1 > 9) { --cn; }
    int cy = 0;
    if (show_d < 1000) { ++cy; }
    if (show_d < 100) { ++cy; }
    if (show_d < 10) { ++cy; }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    if ((u_id > 9999) && ((view == 1) || (view == 4))) cout << c_clock << " [error] " << "Resource Block " << RB_id + 1 << string(cn, ' ') << " || allocated to user " << u_id << string(1, ' ') << " || data left to receive " << show_d << string(cy, ' ') << " b" << "\n";
    else if ((u_id > 999) && ((view == 1) || (view == 4))) cout << c_clock << " [error] " << "Resource Block " << RB_id + 1 << string(cn, ' ') << " || allocated to user " << u_id << string(2, ' ') << " || data left to receive " << show_d << string(cy, ' ') << " b" << "\n";
    else if ((u_id > 99) && ((view == 1) || (view == 4))) cout << c_clock << " [error] " << "Resource Block " << RB_id + 1 << string(cn, ' ') << " || allocated to user " << u_id << string(3, ' ') << " || data left to receive " << show_d << string(cy, ' ') << " b" << "\n";
    else if ((u_id > 9) && ((view == 1) || (view == 4))) cout << c_clock << " [error] " << "Resource Block " << RB_id + 1 << string(cn, ' ') << " || allocated to user " << u_id << string(4, ' ') << " || data left to receive " << show_d << string(cy, ' ') << " b" << "\n";
    else if ((view == 1) || (view == 4)) cout << c_clock << " [error] " << "Resource Block " << RB_id + 1 << string(cn, ' ') << " || allocated to user " << u_id << string(5, ' ') << " || data left to receive " << show_d << string(cy, ' ') << " b" << "\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
  }
}

void Network::NewPropagation(int view, string c_clock, int ms, int time, int initial_phase)
{
  for (auto const& it : buffer_)
  {
    vector<int> rk;
    for (int i = 0; i < RB; i++) rk.push_back(generator_rk->Rand(20, 800));
    it->set_rk(rk);
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
  if ((view == 1) || (view == 5)) cout << c_clock << " [info] " << " New propagation has been set " << "\n";
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}