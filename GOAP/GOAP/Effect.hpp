#ifndef __EFFECT__
#define __EFFECT__

#include <iostream>
#include "World.hpp"

enum Modifier;

class Effect
{
public:
	Effect(const std::string ressource,const Modifier mod);
	Effect(const Effect * const effect);
	~Effect();	
	template<typename V> void ExecuteEffect(World<V> * const world);
	virtual void Execute();
private:
	std::string m_ressource;
	Modifier m_modifier;
};

#endif //!__EFFECT__
