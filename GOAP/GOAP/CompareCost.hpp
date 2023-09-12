#ifndef __COMPARE_COST__
#define __COMPARE_COST__

#include "WorldAction.hpp"

struct CompareCost
{
	bool operator()(const WorldAction* const a, const WorldAction* const b)
	{
		return a->world->GetCost() > b->world->GetCost();
	}
};


#endif //!__COMPARE_COST__