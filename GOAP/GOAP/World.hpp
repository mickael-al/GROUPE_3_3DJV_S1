#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include <iostream>
#include <unordered_map>

template<typename T>//Template pour le type des ressources, dans le cas d'utilisation de plusieurs type utiliser le void*  
class World 
{	
public:
	World(const std::vector<std::string> & variables = std::vector<std::string>(), const std::vector<T> & initValue = std::vector<T>())
	{
		m_mapValue.reserve(variables.size());
		for(int i = 0; i < variables.size(); i++)
		{
			m_mapValue[variables[i]] = initValue.size() > i ? initValue[i]: T();
		}
	}
	World(const World<T>* const world)
	{
		m_mapValue.reserve(world->m_mapValue.size());
		m_mapValue = world->m_mapValue;		
	}
	~World()
	{
		m_mapValue.clear();
	}
	void Copy(const World<T>* const world)
	{
		m_mapValue.clear();
		m_mapValue.reserve(world->m_mapValue.size());
		m_mapValue = world->m_mapValue;
	}
	void ModifyRessource(std::string ressource, T value)
	{		
		m_mapValue[ressource] += value;
	}
	const T & GetRessource(std::string ressource)
	{
		return m_mapValue[ressource];
	}
	void AddRessource(std::string ressource,T value = T())
	{
		m_mapValue[ressource] = value;		
	}
	void Print() const
	{
		for (const auto& pair : m_mapValue)
		{
			std::cout << "Ressource: " << pair.first << ", Valeur: " << pair.second << std::endl;
		}
	}
private:
	std::unordered_map<std::string, T> m_mapValue;
};

#endif //!__WORLD__

