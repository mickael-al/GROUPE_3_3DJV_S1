#ifndef __GOAP_MANAGER__
#define __GOAP_MANAGER__

#include <vector>
class Action;
#include "World.hpp"

class GoapManager final
{
public:
	GoapManager(World<float> * const world, std::vector<Action*> & allActions, std::vector<Action*> & objectifs);
	GoapManager(const GoapManager * const goapManager);	
	~GoapManager();	
	std::vector<const Action*> Resolve();
private:
	void CalculateResolver() const;
private:
	std::vector<Action*> m_allActions;
	std::vector<Action*> m_objectifs;	
	World<float> * m_world;
}; 

#endif //!__GOAP_MANAGER__

