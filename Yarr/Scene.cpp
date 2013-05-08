#include "Scene.h"
#include "Entity.h"

Scene::Scene()
{
}

Scene::Scene(const Scene&)
{
}

Scene::~Scene()
{
}

bool Scene::Initialize()
{
	return true;
}

void Scene::Shutdown()
{
}

Entity* Scene::NewEntity()
{
	Entity* new_entity = new Entity();
	//m_entityList.insert(*new_entity);
	return new_entity;
}

void Scene::GetEntityList(std::set<Entity>& entityList)
{
	//entityList = m_entityList;
	return;
}


