#include "Scene.h"
#include "Entity.h"

Scene::Scene()
{
	m_modelFactory = 0;
}

Scene::Scene(const Scene&)
{
}

Scene::~Scene()
{
}

bool Scene::Initialize(ModelFactory* modelFactory)
{
	m_modelFactory = modelFactory;
	return true;
}

void Scene::Shutdown()
{
	if(m_modelFactory)
	{
		m_modelFactory->Shutdown(); 
		delete m_modelFactory;
		m_modelFactory = 0;
	}
}

bool Scene::NewEntity(std::string entityName, float x, float y, float z)
{
	m_modelFactory->CreateModel(entityName);
	m_entitySet.insert(IntrusivePtr<Entity>(new Entity(entityName, x, y, z)));
	return true;
}

const std::set<IntrusivePtr<Entity> >& Scene::GetEntitySet()
{
	return m_entitySet;
}


