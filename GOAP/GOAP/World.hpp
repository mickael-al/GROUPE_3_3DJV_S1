#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include <iostream>
#include <unordered_map>

template<typename T>//Template pour le type des ressources, dans le cas d'utilisation de plusieurs type utiliser le void*  
class World
{	
public:
	World(const std::vector<std::string> variables);
	World(const World * const world);
	~World();
	void SetRessource(const std::string,T value);
	T GetRessource(const std::string) const;
private:
	std::unordered_map<const std::string, T> m_mapValue;
};

#endif //!__WORLD__

