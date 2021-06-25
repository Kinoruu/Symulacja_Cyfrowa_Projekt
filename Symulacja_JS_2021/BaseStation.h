//#pragma once
#ifndef BASESTATION_H
#define BASESTATION_H
#include <vector>
#include "User.h"

using namespace std;

class BaseStation : public User
{
public:

private:
  unsigned int number_of_users_; // ilo�� u�ytkownik�w zarejstrowanych w stacji bazowej
  vector<User*> user_list_; // wektor u�ytkownik�w
};
#endif