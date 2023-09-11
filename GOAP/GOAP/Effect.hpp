#ifndef __EFFECT__
#define __EFFECT__

class World;

template<typename R>//Peut etre utilisé comme ressource ou sur d'autre objets specifique
class Effect
{
public:
	Effect(R* const ressource);//TODO:ADD Modifier ressource
	Effect(const Effect * const effect);
	~Effect();
	virtual void Execute(World * const world);
private:
	R* const m_ressource;
};

#endif //!__EFFECT__
