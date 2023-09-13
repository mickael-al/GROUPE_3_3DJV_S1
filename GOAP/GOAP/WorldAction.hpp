#ifndef __WORLD_ACTION__
#define __WORLD_ACTION__

#include "World.hpp"
#include "PreCondition.hpp"
class Action;

struct WorldAction
{
	const Action* action;
	World<float>* world;
	std::vector<PreCondition<float>*> allConditions;
	WorldAction* parent;
};

#endif //!__WORLD_ACTION__