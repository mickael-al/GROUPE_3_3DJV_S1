#include "Effect.hpp"
#include "EnumModifier.hpp"

Effect::Effect(const std::string ressource, const Modifier mod)
{
	m_ressource = ressource;
	m_modifier = mod;
}

Effect::Effect(const Effect* const effect)
{
	m_ressource = effect->m_ressource;
	m_modifier = effect->m_modifier;
}

Effect::~Effect()
{
	m_ressource.clear();	
}

std::string Effect::GetRessource() const
{
	return m_ressource;
}

Modifier Effect::GetModifier() const
{
	return m_modifier;
}

template<typename V> void Effect::ExecuteEffect(World<V> * const world)
{	
	world->GetRessource(m_ressource);
	Execute();
}

void Effect::Execute()
{

}