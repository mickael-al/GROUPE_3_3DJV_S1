#include "GoapManager.hpp"
#include "CompareCost.hpp"
#include "Effect.hpp"
#include "EnumModifier.hpp"
#include "Action.hpp"
#include <assert.h>
#include <queue>
#include <algorithm>

GoapManager::GoapManager(World<float> * const world, std::vector<Action*> allActions, std::vector<Action*> objectifs)
{
	m_allActions = allActions;
	m_objectifs = objectifs;
	m_world = world;
	//assert(false && "Objectif n'est pas dans action");
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

	std::priority_queue<ActionCost*, std::vector<ActionCost*>, CompareCondition> openNode;//definie une priorité sur les couts des monde generer par les actions	
	ActionCost* current = nullptr;
	std::vector<PreCondition<float>*> conditions;
	std::vector<ActionCost*> m_allac;
	std::vector<const Action*> actions_resolve;
	std::vector<const Effect*> action_effects;
	ActionCost* firstActionCost = new ActionCost();
	std::vector<WorldAction*> allWorldAction;	

	WorldAction* firstwa = new WorldAction();
	firstwa->action = m_objectifs[0];
	firstwa->world = m_world;

	allWorldAction.push_back(firstwa);

	firstActionCost->action = m_objectifs[0];	
	firstActionCost->m_cost = 0;

	openNode.push(firstActionCost);
	
	while (!openNode.empty())
	{
		current = openNode.top();
		bool checkCond = true;
		conditions = current->action->GetPreConditions();
		for (int i = 0; i < conditions.size() && checkCond; i++)
		{
			if (!conditions[i]->CheckPreCondition(allWorldAction[allWorldAction.size() - 1]->world))
			{
				checkCond = false;
			}
		}
		if (checkCond)
		{
			openNode.pop();
			WorldAction* wa = new WorldAction();
			wa->action = current->action;
			wa->world = new World<float>(allWorldAction[allWorldAction.size() - 1]->world);
			action_effects = wa->action->GetEffects();
			for (int i = 0; i < action_effects.size(); i++)
			{				
				action_effects[i]->ExecuteEffect(wa->world);
			}
			allWorldAction.push_back(wa);	
			if (firstActionCost == current)
			{
				break;
			}
			m_allac.push_back(current);
		}
		
		std::vector<ActionCost*> actionC;
		for (int i = 0; i < conditions.size(); i++)
		{
			if (!conditions[i]->CheckPreCondition(allWorldAction[allWorldAction.size()-1]->world))
			{
				current->allConditions.push_back(conditions[i]);
				actions_resolve = conditions[i]->GetResolver();
				for (int j = 0; j < actions_resolve.size(); j++)
				{
					ActionCost* wa = new ActionCost();
					wa->action = actions_resolve[j];
					actionC.push_back(wa);
					openNode.push(wa);
				}
			}
		}
		for (int i = 0; i < actionC.size(); i++)
		{
			for (int j = 0; j < current->allConditions.size(); j++)
			{
				actionC[i]->allConditions.push_back(current->allConditions[j]);
			}
		}
	}

	std::vector<const Action*> path;
	for (int i = 1; i < allWorldAction.size(); i++)
	{
		path.push_back(allWorldAction[i]->action);
		delete allWorldAction[i]->world;
		delete allWorldAction[i];
	}
	for (int i = 1; i < m_allac.size(); i++)
	{
		delete m_allac[i];
	}

	assert(!path.empty() && "Aucun chemin trouvé.");
	
	return path;
}