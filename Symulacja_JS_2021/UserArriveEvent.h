//#pragma once
#ifndef USER_ARRIVE_EVENT_H_
#define USER_ARRIVE_EVENT_H_

#include "Event.h"
#include "Network.h"
#include <functional>
#include "Simulator.h"

class UserArriveEvent :
  public Event
{
public:
  UserArriveEvent(size_t time, Network* network, EventList* event_list);
  void Execute(int view, string c_clock, int ms, int time, int initial_phase) override;

private:
  EventList* event_list_ = nullptr;
  const size_t max_generate_user = 1;
};
#endif
