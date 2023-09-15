#include "Effect.hpp"
#include "EnumModifier.hpp"

Effect::Effect(const std::string & ressource, const Modifier mod,const float value)
{
	this->m_ressource = ressource;
	this->m_modifier = mod;
	this->m_value = value;
}

Effect::Effect(const Effect* const effect)
{
	this->m_ressource = effect->m_ressource;
	this->m_modifier = effect->m_modifier;
	this->m_value = effect->m_value;
}

Effect::~Effect()
{
	this->m_ressource.clear();
}

const std::string & Effect::GetRessource() const
{
	return this->m_ressource;
}

const Modifier & Effect::GetModifier() const
{
	return this->m_modifier;
}

void Effect::ExecuteEffect(World<float> * const world) const
{	
	world->ModifyRessource(m_ressource, m_modifier == Modifier::ADD ? this->m_value : -this->m_value);
	this->Execute();
}

void Effect::Execute() const
{ 

}