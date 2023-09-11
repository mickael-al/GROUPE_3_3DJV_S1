#ifndef __ACTION__
#define __ACTION__

#include <iostream>
#include <vector>

class Action
{
public:
	Action();
	Action(const Action * const action);
	~Action();
	std::string GetName() const;
	std::vector<Action*> GetTransition() const;
	//void AddTransition(const Action* const action) const;
private:
	std::string m_name;
	//std::vector<Action*> m_transition;
	//std::vector<Action*> m_transition;
};

#endif // !__ACTION__
