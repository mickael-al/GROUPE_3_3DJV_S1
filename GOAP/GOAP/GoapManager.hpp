#ifndef __GOAP_MANAGER__
#define __GOAP_MANAGER__

#include <vector>
class Action;
#include "World.hpp"

class GoapManager final
{
public:
	GoapManager(World<float> * const world, std::vector<const Action*> allActions, std::vector<const Action*> objectifs);
	GoapManager(const GoapManager * const goapManager);	
	~GoapManager();
	void CalculateResolver() const;
	std::vector<const Action*> Resolve() const;
private:
	std::vector<const Action*> m_allActions;
	std::vector<const Action*> m_objectifs;	
	World<float> * m_world;
}; 

#endif //!__GOAP_MANAGER__

