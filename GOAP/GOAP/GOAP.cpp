#include <iostream>
#include "GoapManager.hpp"
#include "Action.hpp"
#include "EnumModifier.hpp"
#include <chrono>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

int main() 
{
	std::vector<Action*> allActions;
	std::vector<Action*> objActions;

	allActions.push_back(new Action("Construire une Maison",2));
	allActions.push_back(new Action("Couper du bois", 2));
	allActions.push_back(new Action("Construire une Hache", 2));
	objActions.push_back(allActions[0]);

	allActions[0]->AddPreCondition(new PreCondition<float>("Bois", Condition::SUP_EQUALS, 10));
	allActions[1]->AddPreCondition(new PreCondition<float>("Hache", Condition::SUP_EQUALS, 1));
	allActions[2]->AddPreCondition(new PreCondition<float>("Bois", Condition::SUP_EQUALS, 3));

	allActions[0]->AddEffect(new Effect("Maison", Modifier::ADD, 1));
	allActions[0]->AddEffect(new Effect("Bois", Modifier::SUB, 10));
	allActions[1]->AddEffect(new Effect("Bois", Modifier::ADD, 1));
	allActions[2]->AddEffect(new Effect("Hache", Modifier::ADD, 1));
	allActions[2]->AddEffect(new Effect("Bois", Modifier::SUB, 3));

	World<float>* world = new World<float>();
	world->AddRessource("Maison", 0);
	world->AddRessource("Bois", 3);
	world->AddRessource("Hache", 0);	
	GoapManager * goap = new GoapManager(world, allActions, objActions);

	auto t0 = Time::now();

	std::vector<const Action*> path = goap->Resolve();
	std::string allPath = "";
	for (int i = 0; i < path.size(); i++)
	{
		allPath += path[i]->GetName() + "\n";
	}
	std::cout << allPath << std::endl;

	auto t1 = Time::now();
	fsec fs = t1 - t0;
	std::cout << fs.count() << "s\n";
	delete goap;
}
