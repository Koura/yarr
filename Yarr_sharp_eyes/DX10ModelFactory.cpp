#include "DX10ModelFactory.h"
#include <iostream>

DX10ModelFactory::DX10ModelFactory()
	: m_modelMap()
{
}

DX10ModelFactory::DX10ModelFactory(const DX10ModelFactory&)
{
}

DX10ModelFactory::~DX10ModelFactory()
{
}

void DX10ModelFactory::CreateModel(std::string modelName)
{
	if(m_device)
	{
		std::pair<std::string,IntrusivePtr<DX10Model> > insertion (modelName, IntrusivePtr<DX10Model>(new DX10Model));
		insertion.second.GetPtr()->Initialize("../Game/Resources/Models/cube.txt", m_device, 1.0, 0.0, 0.0, 1.0);
		m_modelMap.insert(insertion);
	}
}

DX10Model* DX10ModelFactory::GetModelByName(std::string modelName)
{
	std::unordered_map<std::string,IntrusivePtr<DX10Model> >::const_iterator got = m_modelMap.find(modelName);	
	return got->second.GetPtr();
}

void DX10ModelFactory::SetID3D10Device(ID3D10Device* device)
{
	m_device = device;
}

void DX10ModelFactory::Shutdown()
{
	for(auto it = m_modelMap.begin(); it != m_modelMap.end(); ++it)
	{
		it->second.GetPtr()->Shutdown();
	}
}