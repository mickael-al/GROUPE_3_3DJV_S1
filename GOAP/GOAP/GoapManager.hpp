#ifndef __GOAP_MANAGER__
#define __GOAP_MANAGER__

#include <vector>
class Action;
class World;

class GoapManager final
{
public:
	GoapManager(const World * const world, std::vector<const Action*> allActions, std::vector<const Action*> objectifs);
	GoapManager(const GoapManager * const goapManager);
	~GoapManager();
private:
	std::vector<const Action*> m_allActions;
	std::vector<const Action*> m_objectifs;	
};

#endif //!__GOAP_MANAGER__

