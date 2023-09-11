#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include <iostream>
#include <unordered_map>

template<typename T>//Template pour le type des ressources, dans le cas d'utilisation de plusieurs type utiliser le void*  
class World
{	
public:
	World(const std::vector<std::string> variables)
	{
		m_mapValue.reserve(variables.count());
		for(int i = 0; i < variables.count(); i++) 
		{
			this->m_mapValue.insert(variables[i], T());
		}
	}
	World(const World<T>* const world)
	{
		m_mapValue.reserve(world->m_mapValue.count());
		this->m_mapValue = world->m_mapValue;
	}
	~World()
	{
		this->m_mapValue.clear();
	}
	void SetRessource(const std::string ressource, T value)
	{
		this->m_mapValue.insert(ressource, value);
	}
	T GetRessource(const std::string ressource) const
	{
		return this->m_mapValue[ressource];
	}
private:
	std::unordered_map<const std::string, T> m_mapValue;
};

#endif //!__WORLD__

