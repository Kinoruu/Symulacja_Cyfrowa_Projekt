//#pragma once
#ifndef EVENT_H_
#define EVENT_H_

#include "Network.h"
#include <functional>
#include <vector>
#include <queue>
#include <string>

using namespace std;

class Event
{
  public:
    typedef priority_queue<Event*, vector<Event*>, function<bool(Event*, Event*)>> EventList;
    Event(size_t time, Network* network);

    virtual void Execute(int view, string c_clock, int ms, int time, int initial_phase) = 0;

    size_t get_time() { return time_; }
protected:
  size_t time_;
  Network* network_ = nullptr;
};
#endif