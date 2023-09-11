#ifndef __ACTION__
#define __ACTION__

#include <iostream>
#include <vector>

class PreCondition;
class Effect;

class Action final
{
public:
	Action(const std::string name);
	Action(const Action * const action);
	~Action();
	void SetName(const std::string name);
	std::string GetName() const;
	void AddPreCondition(const PreCondition* preCondition);
	std::vector<const PreCondition*> GetPreConditions() const;
	void AddEffect(const Effect* effect);
	std::vector<const Effect*> GetEffects() const;
private:
	std::string m_name;
	std::vector<const PreCondition*> m_preConditions;
	std::vector<const Effect*> m_effects;
};

#endif // !__ACTION__
