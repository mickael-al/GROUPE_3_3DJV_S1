#include "Action.hpp"

Action::Action(const std::string name, const unsigned short couts)
{
	this->m_name = name;
	this->m_couts = couts;
}
Action::Action(const Action* const action)
{
	this->m_name = action->GetName();
	this->m_preConditions = action->GetPreConditions();
	this->m_effects = action->GetEffects();
}
Action::~Action()
{
	this->m_preConditions.clear();
	this->m_effects.clear();
}

void Action::SetName(const std::string name)
{
	this->m_name = name;
}
std::string Action::GetName() const
{
	return this->m_name;
}
void Action::AddPreCondition(const PreCondition* preCondition)
{
	this->m_preConditions.push_back(preCondition);
}
std::vector<const PreCondition*> Action::GetPreConditions() const
{
	return this->m_preConditions;
}
void Action::AddEffect(const Effect* effect)
{
	this->m_effects.push_back(effect);
}
std::vector<const Effect*> Action::GetEffects() const
{
	return this->m_effects;
}

unsigned short Action::GetCouts() const
{
	return this->m_couts;
}

void Action::SetCouts(const unsigned short couts)
{
	this->m_couts = couts;
}