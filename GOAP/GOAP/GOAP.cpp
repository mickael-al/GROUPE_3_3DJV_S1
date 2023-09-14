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

	allActions.push_back(new Action("Construire une Maison", 1));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Bois", Condition::SUP_EQUALS, 10));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Pierre", Condition::SUP_EQUALS, 10));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Maison", Modifier::ADD, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Bois", Modifier::SUB, 10));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Pierre", Modifier::SUB, 10));

	allActions.push_back(new Action("Couper du bois", 2));
	//allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Hache", Condition::INF_EQUALS, 0));
	allActions[allActions.size()-1]->AddEffect(new Effect("Bois", Modifier::ADD, 1));

	allActions.push_back(new Action("Miner de la pierre", 1));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Pioche", Condition::SUP_EQUALS, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Pierre", Modifier::ADD, 2));

	allActions.push_back(new Action("Couper du bois avec une hache", 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Bois", Modifier::ADD, 2));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Hache", Condition::SUP_EQUALS, 1));

	allActions.push_back(new Action("Construire une Hache", 1));	
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Bois", Condition::SUP_EQUALS, 2));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Craft", Condition::SUP_EQUALS, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Hache", Modifier::ADD, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Bois", Modifier::SUB, 2));

	allActions.push_back(new Action("Construire une Pioche", 1));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Bois", Condition::SUP_EQUALS, 2));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Craft", Condition::SUP_EQUALS, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Pioche", Modifier::ADD, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Bois", Modifier::SUB, 2));

	allActions.push_back(new Action("Construire une table de craft", 1));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Bois", Condition::SUP_EQUALS, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Craft", Modifier::ADD, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Bois", Modifier::SUB, 1));

	objActions.push_back(allActions[0]);
	
	World<float>* world = new World<float>();
	world->AddRessource("Maison", 0);
	world->AddRessource("Bois", 0);
	world->AddRessource("Hache", 0);	
	world->AddRessource("Pioche", 0);
	world->AddRessource("Craft", 0);
	world->AddRessource("Pierre", 0);

	GoapManager * goap = new GoapManager(world, allActions, objActions);

	auto t0 = Time::now();

	std::vector<const Action*> path = goap->Resolve();
	std::string allPath = "";
	for (int i = path.size()-1; i >= 0; i--)
	{
		allPath += path[i]->GetName() + "\n";
	}
	std::cout << allPath << std::endl;

	auto t1 = Time::now();
	fsec fs = t1 - t0;
	std::cout << fs.count() << "s\n";
	delete goap;
}
