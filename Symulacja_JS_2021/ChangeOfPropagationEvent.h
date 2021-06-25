//#pragma once
#ifndef CHANGE_OF_PROPAGATION_EVENT_H_
#define CHANGE_OF_PROPAGATION_EVENT_H_

#include "Event.h"
#include "Network.h"
#include <functional>

class ChangeOfPropagationEvent :
  public Event
{
public:
  ChangeOfPropagationEvent(size_t time, Network* network, EventList* event_list);

  void Execute(int view, string c_clock, int ms, int time, int initial_phase) override;

private:
  EventList* event_list_ = nullptr;
  const size_t propagation_time = 15;
};

#endif
