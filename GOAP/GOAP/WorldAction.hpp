#ifndef __WORLD_ACTION__
#define __WORLD_ACTION__

#include "PreCondition.hpp"
#include "World.hpp"
#include <vector>

class Action;

struct WorldAction
{
	std::vector<const Action*> openNode;
	const Action* action;
	World<float> * world;
	WorldAction* parent;
	unsigned short cost = 0;
};

#endif //!__WORLD_ACTION__