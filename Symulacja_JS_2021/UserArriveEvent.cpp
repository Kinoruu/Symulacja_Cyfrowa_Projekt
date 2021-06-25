#include "UserArriveEvent.h"
#include "Network.h"

UserArriveEvent::UserArriveEvent(size_t time, Network* network, EventList* event_list) : Event(time, network), event_list_(event_list)
{
}

void UserArriveEvent::Execute(int view, string c_clock, int ms, int time, int initial_phase)
{
  double lambda = network_->get_lambda();
  network_->Generateuser(view, c_clock, ms, time, initial_phase);
  event_list_->push(new UserArriveEvent(time_ + (network_->generator_t->RandExp(lambda)), network_, event_list_));
} 