#include "GoapManager.hpp"
#include "CompareCost.hpp"
#include "PreCondition.hpp"
#include "Effect.hpp"
#include "EnumModifier.hpp"
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
		return std::vector<const Action*>();
	}

	std::priority_queue<const Action*, std::vector<const Action*>, CompareCost> openAction;//definie une priorité sur le couts des actions
	std::sort(m_objectifs.begin(), m_objectifs.end(), CompareCost::operator());
	openAction.push(m_objectifs[0]);
	const Action* currentAction = nullptr;

	/*
	Recherche : Tant que la file de priorité n'est pas vide, vous effectuez les étapes suivantes :
a. Retirez le nœud avec le coût total le plus bas de la file de priorité. Ce nœud est généralement l'état cible que vous essayez d'atteindre.
b. Si le nœud actuel est le point de départ, vous avez trouvé un chemin optimal.

c. Sinon, pour chaque action possible à partir de l'état actuel, calculez l'état résultant en appliquant l'action inverse (puisque vous suivez le chemin inverse). Vérifiez si les préconditions de l'action inverse sont satisfaites dans l'état actuel. Si oui, mettez à jour le nœud pour représenter l'état résultant de l'action inverse, mettez à jour le coût total, et ajoutez le nœud à la file de priorité avec le nouveau coût total estimé (coût actuel + estimation du coût restant pour atteindre le point de départ).
	*/
	std::vector<PreCondition<float>*> conditions;
	std::vector<const Action*> actions_resolve;
	while (!openAction.empty())
	{
		currentAction = openAction.top();
		openAction.pop();
		conditions = currentAction->GetPreConditions();
		for (int i = 0; i < conditions.size(); i++)
		{
			if (!conditions[i]->CheckPreCondition(m_world))
			{
				actions_resolve = conditions[i]->GetResolver();
				for (int j = 0; j < actions_resolve.size(); j++)
				{
					openAction.push(actions_resolve[j]);
				}
			}
		}
	}

	// Si la file de priorité est vide et que rien a ététrouver pour le premier objectif
	return std::vector<const Action*>();
}