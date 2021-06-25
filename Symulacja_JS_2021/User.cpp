#include "User.h"

User::User(int d, vector<int> rk, double ar, size_t id, int ubn, bool uaf, User *next) : data_size_d_(d), bit_rate_(rk), avg_rk_(ar), user_id_(id), user_blocks_number_(ubn), user_avg_flag_(uaf), next_(next)
{
}