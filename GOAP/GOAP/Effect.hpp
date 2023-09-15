#ifndef __EFFECT__
#define __EFFECT__

#include <iostream>
#include "World.hpp"

enum Modifier;

class Effect
{
public:
	Effect(const std::string & ressource,const Modifier mod,const float value);
	Effect(const Effect * const effect);
	~Effect();	
	const std::string & GetRessource() const;
	const Modifier & GetModifier() const;
	void ExecuteEffect(World<float> * const world) const;
	virtual void Execute() const;
private:
	std::string m_ressource;	
	Modifier m_modifier;
	float m_value;
};

#endif //!__EFFECT__
