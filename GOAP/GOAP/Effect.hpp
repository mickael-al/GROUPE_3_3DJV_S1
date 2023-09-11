#ifndef __EFFECT__
#define __EFFECT__

#include <iostream>

class World;
enum Modifier;

class Effect
{
public:
	Effect(const std::string ressource,const Modifier mod);
	Effect(const Effect * const effect);
	~Effect();
	virtual void Execute(World * const world);
private:
	std::string m_ressource;
	Modifier m_modifier;
};

#endif //!__EFFECT__
