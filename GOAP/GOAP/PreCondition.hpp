#ifndef __PRE_CONDITION__
#define __PRE_CONDITION__

template<typename T>
class PreCondition
{
public:
	PreCondition();
	PreCondition(const PreCondition * const preCondition);
	~PreCondition();
	virtual bool Check();
private:
	T value;
};

#endif //!__PRE_CONDITION__

