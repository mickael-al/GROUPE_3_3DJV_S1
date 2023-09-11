#ifndef __PRE_CONDITION__
#define __PRE_CONDITION__

enum Condition;
class World;

template<typename T>
class PreCondition
{
public:
	PreCondition(Condition condition,T value);
	PreCondition(const PreCondition * const preCondition);
	~PreCondition();
	virtual bool Check(const World * const world) const;
private:
	T m_value;
};

#endif //!__PRE_CONDITION__

