#ifndef __WORLD_ACTION__
#define __WORLD_ACTION__

#include "PreCondition.hpp"
#include "World.hpp"

class Action;

struct ActionCost
{
	const Action* action;
	std::vector<PreCondition<float>*> allConditions;
	unsigned short m_cost = 0;
};

struct WorldAction
{
	const Action* action;
	World<float> * world;
};

#endif //!__WORLD_ACTION__