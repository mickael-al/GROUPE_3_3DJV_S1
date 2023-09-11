#include "GoapManager.hpp"

GoapManager::GoapManager(World<float> * const world, std::vector<const Action*> allActions, std::vector<const Action*> objectifs)
{
	m_allActions = allActions;
	m_objectifs = objectifs;
	m_world = world;
}

GoapManager::GoapManager(const GoapManager* const goapManager)
{

}

GoapManager::~GoapManager()
{

}