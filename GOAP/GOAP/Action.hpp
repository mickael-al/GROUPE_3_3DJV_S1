#ifndef __ACTION__
#define __ACTION__

#include <iostream>
#include <vector>

class PreCondition;
class Effect;

class Action final
{
public:
	Action();
	Action(const Action * const action);
	~Action();
	std::string GetName() const;
	void AddPreCondition(const PreCondition* preCondition);
	std::vector<const PreCondition*> getPreConditions() const;
	void AddEffect(const Effect* effect);
	std::vector<const Effect*> getEffects() const;
private:
	std::string m_name;
	std::vector<const PreCondition*> m_preConditions;
	std::vector<const Effect*> m_effects;
};

#endif // !__ACTION__
