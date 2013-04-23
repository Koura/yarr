#include "Scene.h"

Scene::Scene()
	: m_entityList()
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

bool Scene::NewEntity()
{
	return true;
}

void Scene::GetEntityList(std::set<Entity>& entityList)
{
	entityList = m_entityList;
	return;
}


