#include "ChangeOfPropagationEvent.h"

#include "Event.h"

ChangeOfPropagationEvent::ChangeOfPropagationEvent(size_t time, Network* network, EventList* event_list) : Event(time, network), event_list_(event_list)
{
}

void ChangeOfPropagationEvent::Execute(int view, string c_clock, int ms, int time, int initial_phase)
{
  network_->NewPropagation(view, c_clock, ms, time, initial_phase);
  event_list_->push(new ChangeOfPropagationEvent(time_ + propagation_time, network_, event_list_));
}