#include "ResourceBlock.h"
#include <vector>

ResourceBlock::ResourceBlock(size_t RB_id, size_t u_id, bool e, size_t rk) : RB_id_(RB_id), user_id_(u_id), error_(e), bit_rate_(rk)
{
}