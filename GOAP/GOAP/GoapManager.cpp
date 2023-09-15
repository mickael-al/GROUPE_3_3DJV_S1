#include "GoapManager.hpp"
#include "CompareCost.hpp"
#include "Effect.hpp"
#include "EnumModifier.hpp"
#include "Action.hpp"
#include <assert.h>
#include <queue>
#include <algorithm>

GoapManager::GoapManager(World<float> * const world, std::vector<Action*> & allActions, std::vector<Action*> & objectifs)
{
	m_allActions = allActions;
	m_objectifs = objectifs;
	m_world = world;
	for (int i = 0; i < m_objectifs.size(); i++)
	{
		bool isExist = false;
		for (int j = 0; j < m_allActions.size() && !isExist; j++)
		{
			if (m_allActions[j] == m_objectifs[i])
			{
				isExist = true;
			}
		}
		if (!isExist)
		{
			assert(false && "Objectif n'est pas dans action");
		}
	}	
	CalculateResolver();
}

GoapManager::GoapManager(const GoapManager* const goapManager)
{

}

GoapManager::~GoapManager()
{

}

void GoapManager::CalculateResolver() const
{
	std::vector<PreCondition<float>*> precondition;
	std::vector<PreCondition<float>*> local_precondition;
	for (int i = 0; i < m_allActions.size(); i++)
	{
		local_precondition = m_allActions[i]->GetPreConditions();
		for (int j = 0; j < local_precondition.size(); j++)
		{
			if (std::find(precondition.begin(), precondition.end(), local_precondition[j]) == precondition.end())
			{
				precondition.push_back(local_precondition[j]);
			}
		}
	}
	std::vector<const Effect*> local_effects;
	for (int p = 0; p < precondition.size(); p++)
	{
		std::vector<const Action*> effect_to_actions;		
		for (int i = 0; i < m_allActions.size(); i++)
		{
			local_effects = m_allActions[i]->GetEffects();
			for (int j = 0; j < local_effects.size(); j++)
			{
				if (precondition[p]->GetRessource() == local_effects[j]->GetRessource() && std::find(effect_to_actions.begin(), effect_to_actions.end(), m_allActions[i]) == effect_to_actions.end())
				{
					Condition cond = precondition[p]->GetCondition();

					if (((cond == Condition::INF || cond == Condition::INF_EQUALS) && local_effects[j]->GetModifier() == Modifier::SUB) ||
						((cond == Condition::SUP || cond == Condition::SUP_EQUALS) && local_effects[j]->GetModifier() == Modifier::ADD) ||
						(cond == Condition::DIFF || cond == Condition::EQUALS))
					{
						effect_to_actions.push_back(m_allActions[i]);
					}

				}
			}
		}
		precondition[p]->SetResolver(effect_to_actions);
	}

	for (int i = 0; i < precondition.size(); i++)
	{
		std::string allAction;
		std::vector<const Action*> resolver = precondition[i]->GetResolver();
		for (int j = 0; j < resolver.size(); j++)
		{
			allAction += resolver[j]->GetName() + " ";
		}
		std::cout << "Precondition : " << precondition[i]->GetRessource() << " -> " << allAction << std::endl;
	}
}

std::vector<const Action*> GoapManager::Resolve() const//reverse AStar
{
	if (m_objectifs.empty()) 
	{
		// Si le vector est vide
		assert(false && "Aucun objectif à résoudre.");
		return std::vector<const Action*>();
	}
	std::priority_queue<WorldAction*, std::vector<WorldAction*>, CompareCost> openWorldAction;
	const Action* current = nullptr;
	WorldAction* currentWorldAction = nullptr;
	std::vector<PreCondition<float>*> conditions;
	std::vector<const Action*> actions_resolve;
	std::vector<const Effect*> action_effects;
	WorldAction* firstwa = new WorldAction();
	
	
	std::vector<WorldAction*> worlActionRessource;
	firstwa->openNode.push_back(m_objectifs[0]);	
	firstwa->action = m_objectifs[0];
	firstwa->world = new World<float>(m_world);
	firstwa->cost = 0.0f;
	
	openWorldAction.push(firstwa);
	WorldAction* finalAction = nullptr;
	WorldAction* wa = nullptr;
	bool popCurrentWorld = false;
	bool checkCond = false;
	bool isInOpenNode = false;
	int curindex, i, j, s;
	while (!openWorldAction.empty() && finalAction == nullptr)
	{		
		currentWorldAction = openWorldAction.top();
		popCurrentWorld = false;
		std::vector<const Action*> action_allready_add;
		for (curindex = 0; curindex < currentWorldAction->openNode.size(); curindex++)
		{
			current = currentWorldAction->openNode[curindex];
			conditions = current->GetPreConditions();
			checkCond = true;
			for (i = 0; i < conditions.size() && checkCond; i++)
			{
				if (!conditions[i]->CheckPreCondition(currentWorldAction->world))
				{
					checkCond = false;
					actions_resolve = conditions[i]->GetResolver();
					for (j = 0; j < actions_resolve.size(); j++)
					{
						isInOpenNode = false;
						for (s = 0; s < currentWorldAction->openNode.size() && !isInOpenNode; s++)
						{
							if (currentWorldAction->openNode[s] == actions_resolve[j])
							{
								isInOpenNode = true;
							}
						}
						if (!isInOpenNode)
						{
							currentWorldAction->openNode.push_back(actions_resolve[j]);
						}
					}							
				}
			}
			if (checkCond)
			{
				if (!popCurrentWorld)
				{
					openWorldAction.pop();
					popCurrentWorld = true;
				}
				currentWorldAction->openNode.erase(currentWorldAction->openNode.begin() + curindex);
				curindex--;
				
				isInOpenNode = false;
				for (s = 0; s < action_allready_add.size() && !isInOpenNode; s++)
				{
					if (action_allready_add[s] == current)
					{
						isInOpenNode = true;
					}
				}
				if (!isInOpenNode)//optimize recherche remove double action
				{
					wa = new WorldAction();
					wa->action = current;
					wa->openNode = currentWorldAction->openNode;
					wa->parent = currentWorldAction;
					wa->world = new World<float>(currentWorldAction->world);
					wa->cost += current->GetCost() + currentWorldAction->cost;
					action_effects = current->GetEffects();
					action_allready_add.push_back(current);
					for (int i = 0; i < action_effects.size(); i++)
					{
						action_effects[i]->ExecuteEffect(wa->world);
					}
					openWorldAction.push(wa);			
					if (firstwa->action == wa->action)
					{
						finalAction = wa;
					}
				}
			}		
		}		
	}

	std::vector<const Action*> path;
	while (finalAction != nullptr)
	{
		if (finalAction->parent == nullptr)
		{
			break;
		}
		path.push_back(finalAction->action);
		finalAction = finalAction->parent;
	}

	for (int i = 0; i < worlActionRessource.size(); i++)
	{
		delete worlActionRessource[i]->world;
		delete worlActionRessource[i];
	}
	worlActionRessource.clear();
	assert(!path.empty() && "Aucun chemin trouvé.");
	
	return path;
}