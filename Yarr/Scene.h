#ifndef _SCENE_H_
#define _SCENE_H_


#include "Entity.h"
#include <set>

class Scene
{
public:
	Scene();
	Scene(const Scene&);
	~Scene();
	bool Initialize();
	void Shutdown();
	bool NewEntity();
	void GetEntityList(std::set<Entity>&);
	Entity* GetCamera();

private:
	std::set<Entity> m_entityList;
	Entity* m_camera;
};
#endif