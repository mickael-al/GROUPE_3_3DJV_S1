#ifndef __COMPARE_COST__
#define __COMPARE_COST__

#include "WorldAction.hpp"

struct CompareCost
{
	bool operator()(const WorldAction* const a, const WorldAction* const b)
	{
		return a->cost > b->cost && a->openNode.size() > b->openNode.size();
	}
};

#endif //!__COMPARE_COST__