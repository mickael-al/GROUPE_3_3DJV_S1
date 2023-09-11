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
	~PreCondition();
	template<typename V> bool CheckPreCondition(const World<V> * const world) const;
	virtual void Check();
private:
	std::string m_ressource;
	Condition m_condition;
	T m_value;
};

#endif //!__PRE_CONDITION__

