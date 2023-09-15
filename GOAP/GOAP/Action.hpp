#ifndef __ACTION__
#define __ACTION__

#include <iostream>
#include <vector>
#include "PreCondition.hpp"

class Effect;

class Action final
{
public:
	Action(const std::string & name,const unsigned short cost = 1);
	Action(const Action * const action);
	~Action();
	void SetName(const std::string & name);
	const std::string & GetName() const;
	unsigned short GetCost() const;
	void SetCost(const unsigned short couts);
	void AddPreCondition(PreCondition<float>* preCondition);
	const std::vector<PreCondition<float>*> & GetPreConditions() const;
	void AddEffect(const Effect* effect);
	const std::vector<const Effect*> & GetEffects() const;
private:
	std::string m_name;
	std::vector<PreCondition<float>*> m_preConditions;
	std::vector<const Effect*> m_effects;
	unsigned short m_cost;
};

#endif // !__ACTION__
