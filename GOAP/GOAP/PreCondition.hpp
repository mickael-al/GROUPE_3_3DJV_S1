#ifndef __PRE_CONDITION__
#define __PRE_CONDITION__

#include <iostream>
#include "World.hpp"
#include "EnumCondition.hpp"

template<typename T>
class PreCondition
{
public:
	PreCondition(const std::string ressource, const Condition condition, const T value)
	{
		m_ressource = ressource;
		m_condition = condition;
		m_value = value;
	}
	PreCondition(const PreCondition* const preCondition)
	{
		m_ressource = preCondition->m_ressource;
		m_condition = preCondition->m_condition;
		m_value = preCondition->m_value;
	}
	~PreCondition()
	{
		m_ressource.clear();
	}
	virtual void Check()
	{

	}
	bool CheckPreCondition(const World<T>* const world) const
	{
		Check();
		const T value = world->GetRessource(m_ressource);
		switch (m_condition)
		{
			case Condition::EQUALS:
				return value == m_value;
			case Condition::INF:
				return value < m_value;
			case Condition::SUP:
				return value > m_value;
			case Condition::INF_EQUALS:
				return value <= m_value;
			case Condition::SUP_EQUALS:
				return value >= m_value;
			case Condition::DIFF:
				return value != m_value;
			default:
				return false;
		}

		return false;
	}	
private:
	std::string m_ressource;
	Condition m_condition;
	T m_value;
};

#endif //!__PRE_CONDITION__

