#ifndef __PRE_CONDITION__
#define __PRE_CONDITION__

#include <iostream>

class World;
enum Condition;

template<typename T>
class PreCondition
{
public:
	PreCondition(const std::string ressource,const Condition condition,const T value);
	PreCondition(const PreCondition * const preCondition);
	~PreCondition();
	virtual bool Check(const World * const world) const;
private:
	std::string m_ressource;
	Condition m_condition;
	T m_value;
};

#endif //!__PRE_CONDITION__

