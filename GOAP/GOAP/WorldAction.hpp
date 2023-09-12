#ifndef __WORLD_ACTION__
#define __WORLD_ACTION__

#include "World.hpp"
class Action;

struct WorldAction
{
	const Action* action;
	World<float>* world;
	WorldAction* parent;
};

#endif //!__WORLD_ACTION__