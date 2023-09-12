#ifndef __COMPARE_COST__
#define __COMPARE_COST__

#include "Action.hpp"

struct CompareCost
{
	bool operator()(const Action*const a,const Action*const b)
	{
		return a->GetCost() > b->GetCost();
	}
};


#endif //!__COMPARE_COST__