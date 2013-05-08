#pragma once
class Entity;
#include "ModelFactory.h"
#include "IntrusivePtr.h"
#include <set>

class Scene
{
public:
	Scene();
	Scene(const Scene&);
	~Scene();
	bool Initialize(ModelFactory*);
	void Shutdown();
	bool NewEntity(std::string, float, float, float);
	const std::set<IntrusivePtr<Entity> >& GetEntitySet();
private:
	std::set<IntrusivePtr<Entity> > m_entitySet;
	ModelFactory* m_modelFactory;
};