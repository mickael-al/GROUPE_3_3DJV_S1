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
		this->m_mapValue.reserve(variables.size());
		for(int i = 0; i < variables.size(); i++)
		{
			this->m_mapValue.insert(variables[i], T());
		}
	}
	World(const World<T>* const world)
	{
		this->m_mapValue.reserve(world->m_mapValue.size());
		this->m_mapValue = world->m_mapValue;
		this->m_cost = world->m_cost;
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
	void AddCost(const unsigned short cost)
	{
		m_cost = cost;
	}
	unsigned short GetCost() const
	{
		return m_cost;
	}
	void ClearCost() const
	{
		m_cost = 0;
	}
private:
	std::unordered_map<const std::string, T> m_mapValue;
	unsigned short m_cost = 0;
};

#endif //!__WORLD__

