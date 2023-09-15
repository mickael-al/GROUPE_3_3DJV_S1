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

	allActions.push_back(new Action("Miner du Diamant", 1));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Pioche en Fer", Condition::SUP_EQUALS, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Diamant", Modifier::ADD, 1));

	allActions.push_back(new Action("Construire une Pioche en Fer", 1));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Bois", Condition::SUP_EQUALS, 1));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Fer", Condition::SUP_EQUALS, 3));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Craft", Condition::SUP_EQUALS, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Pioche en Fer", Modifier::ADD, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Fer", Modifier::SUB, 3));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Bois", Modifier::SUB, 1));

	allActions.push_back(new Action("Faire fondre du Fer", 1));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Four", Condition::SUP_EQUALS, 1));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Minerais de Fer", Condition::SUP_EQUALS, 1));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Charbon", Condition::SUP_EQUALS, 0.1f));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Fer", Modifier::ADD, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Minerais de Fer", Modifier::SUB, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Charbon", Modifier::SUB, 0.1f));

	allActions.push_back(new Action("Construire un Four", 1));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Pierre", Condition::SUP_EQUALS, 8));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Maison", Condition::SUP_EQUALS, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Pierre", Modifier::SUB, 8));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Four", Modifier::ADD, 1));

	allActions.push_back(new Action("Couper du bois", 2));	
	allActions[allActions.size()-1]->AddEffect(new Effect("Bois", Modifier::ADD, 1.0));

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

	allActions.push_back(new Action("Construire une Pioche en Pierre", 1));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Bois", Condition::SUP_EQUALS, 1));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Pierre", Condition::SUP_EQUALS, 3));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Craft", Condition::SUP_EQUALS, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Pioche en Pierre", Modifier::ADD, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Pierre", Modifier::SUB, 3));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Bois", Modifier::SUB, 1));

	allActions.push_back(new Action("Miner du Fer", 1));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Pioche en Pierre", Condition::SUP_EQUALS, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Minerais de Fer", Modifier::ADD, 1));

	allActions.push_back(new Action("Miner du Charbon", 1));
	allActions[allActions.size() - 1]->AddPreCondition(new PreCondition<float>("Pioche en Pierre", Condition::SUP_EQUALS, 1));
	allActions[allActions.size() - 1]->AddEffect(new Effect("Charbon", Modifier::ADD, 1));

	objActions.push_back(allActions[0]);
	objActions.push_back(allActions[1]);

	World<float>* world = new World<float>();
	world->AddRessource("Maison", 0);
	world->AddRessource("Bois", 0);
	world->AddRessource("Hache", 0);	
	world->AddRessource("Pioche", 0);
	world->AddRessource("Craft", 0);
	world->AddRessource("Pierre", 0);
	world->AddRessource("Fer", 0);
	world->AddRessource("Four", 0);
	world->AddRessource("Pioche en Fer", 0);
	world->AddRessource("Pioche en Pierre", 0);
	world->AddRessource("Charbon", 0);
	world->AddRessource("Diamant", 0);
	world->AddRessource("Minerais de Fer", 0);

	GoapManager * goap = new GoapManager(world, allActions, objActions);

	auto t0 = Time::now();
	for (int i = 0; i < objActions.size(); i++)
	{
		std::string allPath = "";
		std::vector<const Action*> path = goap->Resolve();
		
		for (int i = path.size() - 1; i >= 0; i--)
		{
			allPath += path[i]->GetName() + "\n";
		}
		std::cout << allPath << std::endl;
	}
	auto t1 = Time::now();
	fsec fs = t1 - t0;
	std::cout << fs.count() << "s\n";
	delete goap;
}
