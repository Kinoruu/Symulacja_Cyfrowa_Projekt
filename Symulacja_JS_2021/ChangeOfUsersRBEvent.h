//#pragma once
#ifndef CHANGE_OF_USER_RB_EVENT_H_
#define CHANGE_OF_USER_RB_EVENT_H_

#include "Event.h"
#include "Network.h"
#include <functional>

class ChangeOfUsersRBEvent :
  public Event
{
public:
  ChangeOfUsersRBEvent(size_t time, Network* network, EventList* event_list);

  void Execute(int view, string c_clock, int ms, int time, int initial_phase) override;

private:
  EventList* event_list_ = nullptr;
  const size_t allocation_time = 5;
};
#endif