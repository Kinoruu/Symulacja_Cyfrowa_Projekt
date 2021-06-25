#include "Simulator.h"
#include "Event.h"
#include <iostream>
#include "UserArriveEvent.h"
#include "ChangeOfUsersRBEvent.h"
#include "ChangeOfPropagationEvent.h"
#include "Network.h"
#include "User.h"
#include <windows.h>
#include <ctime>
#include <stdlib.h>
#include <string> 
#include <conio.h>
#include "Generators.h"

using namespace std;

Simulator::Simulator(Network* network) : network_(network)
{
}

void Simulator::Simulation(int time, int tryb, int view, int initial_phase, int end, int max_user_served, double lambda)
{
  clock_ = 0;
  network_->Init(time);
  network_->ser_generate_timer(1);
  cout << "Started Simulation method M2: \n"; // Algorithm A2a

  auto cmp = [](Event* left, Event* right) { return left->get_time() > right->get_time(); };
  Event::EventList event_list(cmp);

  event_list.push(new ChangeOfUsersRBEvent(allocation_time, network_, &event_list));                // zdarzenie czasowe - przydzia³ bloków zasobów
  event_list.push(new UserArriveEvent(clock_ + network_->generator_t->RandExp(lambda), network_, &event_list));          // zdarzenie czasowe - pojawienie siê u¿ytkownika 
  event_list.push(new ChangeOfPropagationEvent(network_->generator_tau->RandExp(lambda_tau), network_, &event_list)); // zdarzenie czasowe - zmiana warunków propagacji 

  while (((clock_ < static_cast<size_t>(time)) && (end == 1))  || ((end == 2) && (max_user_served > network_->get_nous())))
  {
    if (tryb == 1)
    {
      if (getchar())
      {
        Event* event = event_list.top();
        event_list.pop();
        clock_ = event->get_time();
        size_t m = clock_ / 60000;
        size_t s = (clock_ - (m * 60000)) / 1000;
        size_t ms = (clock_ - (m * 60000) - (s * 0000)); // / 10;
        string mx, sx, msx; 
        if (m < 10) mx = "0" + to_string(m);
        else mx = to_string(m);
        if (s < 10) sx = "0" + to_string(s);
        else sx = to_string(s);
        if (ms < 1) msx = "00" + to_string(ms);
        else if (ms < 10) msx = "00" + to_string(ms);
        else if (ms < 100) msx = "0" + to_string(ms);
        else msx = to_string(ms);
        c_clock = "[" + mx + ":" + sx + ":" + msx + "]";
        event->Execute(view, c_clock, ms, time, initial_phase);
      }
    }
    else if (tryb == 2)
    {
      Event* event = event_list.top();
      event_list.pop();
      clock_ = event->get_time();
      Sleep(0);
      size_t m = clock_ / 60000;
      size_t s = (clock_ - (m * 60000)) / 1000;
      size_t ms = (clock_ - (m * 60000) - (s * 1000));// / 10;
      string mx, sx, msx; 
      if (m < 10) mx = "0" + to_string(m);
      else mx = to_string(m);
      if (s < 10) sx = "0" + to_string(s);
      else sx = to_string(s);
      if (ms < 1) msx = "00" + to_string(ms);
      else if (ms < 10) msx = "00" + to_string(ms);
      else if (ms < 100) msx = "0" + to_string(ms);
      else msx = to_string(ms);
      c_clock = "[" + mx + ":" + sx + ":" + msx + "]";
      event->Execute(view, c_clock, clock_, time, initial_phase);
    }
  }
}