#pragma once
class Entity;
#include <set>

class Scene
{
public:
	Scene();
	Scene(const Scene&);
	~Scene();
	bool Initialize();
	void Shutdown();
	Entity* NewEntity();
	void GetEntityList(std::set<Entity>&);

private:
	//std::set<Entity> m_entityList;
};