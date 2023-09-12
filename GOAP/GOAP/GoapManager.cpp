#include "GoapManager.hpp"
#include "CompareCost.hpp"
#include "PreCondition.hpp"
#include "Effect.hpp"
#include "EnumModifier.hpp"
#include "Action.hpp"
#include <assert.h>
#include <queue>
#include <algorithm>

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
}

std::vector<const Action*> GoapManager::Resolve() const//reverse AStar
{
	if (m_objectifs.empty()) 
	{
		// Si le vector est vide
		assert(false && "Aucun objectif à résoudre.");
		return std::vector<const Action*>();
	}

	std::priority_queue<WorldAction*, std::vector<WorldAction*>, CompareCost> openWorlds;//definie une priorité sur les couts des monde generer par les actions	
	WorldAction* current;
	std::vector<PreCondition<float>*> conditions;
	std::vector<const Action*> actions_resolve;
	std::vector<const Effect*> action_effects;
	WorldAction* firstWorldAction = new WorldAction();
	std::vector<WorldAction*> allWorldAction;
	allWorldAction.reserve(100);

	firstWorldAction->action = m_objectifs[0];
	firstWorldAction->world = m_world;
	firstWorldAction->parent = nullptr;
	openWorlds.push(firstWorldAction);	
	m_world->ClearCost();	
	
	while (!openWorlds.empty())//https://www.youtube.com/watch?v=D9Xh-zD1f4E
	{
		current = openWorlds.top();
		openWorlds.pop();
		allWorldAction.push_back(current);

		conditions = current->action->GetPreConditions();
		for (int i = 0; i < conditions.size(); i++)
		{
			if (!conditions[i]->CheckPreCondition(current->world))
			{
				actions_resolve = conditions[i]->GetResolver();
				assert(!actions_resolve.empty() && "Aucune action de résolution trouvée.");
				for (int j = 0; j < actions_resolve.size(); j++)
				{
					WorldAction* nwa = new WorldAction();
					nwa->action = actions_resolve[j];
					nwa->world = new World<float>(current->world);
					nwa->world->AddCost(nwa->action->GetCost());
					action_effects = nwa->action->GetEffects();
					for (int a = 0; a < action_effects.size(); a++)
					{
						action_effects[a]->ExecuteEffect(nwa->world);
					}
					nwa->parent = current;
					openWorlds.push(nwa);
				}
			}
		}		
	}

	std::vector<const Action*> path;
	while (current != nullptr)
	{
		path.push_back(current->action);
		current = current->parent;
	}

	assert(!path.empty() && "Aucun chemin trouvé.");

	current = allWorldAction[0];
	allWorldAction.erase(allWorldAction.begin());
	delete current;
	for (int i = 0; i < allWorldAction.size(); i++)
	{
		delete allWorldAction[i]->world;
		delete allWorldAction[i];
	}
	
	return path;
}