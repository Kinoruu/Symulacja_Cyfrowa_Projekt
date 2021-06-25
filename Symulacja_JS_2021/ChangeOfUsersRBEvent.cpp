#include "ChangeOfUsersRBEvent.h"

ChangeOfUsersRBEvent::ChangeOfUsersRBEvent(size_t time, Network* network, EventList* event_list) : Event(time, network), event_list_(event_list)
{
}

void ChangeOfUsersRBEvent::Execute(int view, string c_clock, int ms, int time, int initial_phase)
{
  network_->ResourceAllocation(view, c_clock, ms, time, initial_phase);
  event_list_->push(new ChangeOfUsersRBEvent(time_ + allocation_time, network_, event_list_));
}