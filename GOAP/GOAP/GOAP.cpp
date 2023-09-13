#include <iostream>
#include "GoapManager.hpp"
#include "Action.hpp"
#include "EnumModifier.hpp"

int main() 
{
	std::vector<std::string> ressource
	{
		"Bois",
		"Maison"
	};
	std::vector<float> initRessource
	{
		0,
		1
	};
	std::vector<Action*> allActions;
	std::vector<Action*> objActions;

	allActions.push_back(new Action("Construire une Maison",5));
	allActions.push_back(new Action("Couper du bois", 1));
	objActions.push_back(allActions[0]);

	allActions[0]->AddPreCondition(new PreCondition<float>("Bois", Condition::SUP_EQUALS, 10));
	allActions[0]->AddEffect(new Effect("Maison", Modifier::ADD, 1));
	allActions[0]->AddEffect(new Effect("Bois", Modifier::SUB, 10));
	allActions[1]->AddEffect(new Effect("Bois", Modifier::ADD, 1));

	World<float>* world = new World<float>(ressource, initRessource);
	GoapManager * goap = new GoapManager(world, allActions, objActions);

	std::vector<const Action*> path = goap->Resolve();
	std::string allPath = "";
	for (int i = 0; i < path.size(); i++)
	{
		allPath += path[i]->GetName() + "\n";
	}
	std::cout << allPath << std::endl;
	delete goap;
}
