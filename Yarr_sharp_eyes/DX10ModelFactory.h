#pragma once

#include "ModelFactory.h"
#include "DX10Model.h"
#include "IntrusivePtr.h"
#include <unordered_map>

class DX10ModelFactory : public ModelFactory
{
public:
	DX10ModelFactory();
	DX10ModelFactory(const DX10ModelFactory&);
	~DX10ModelFactory();
	void CreateModel(std::string);
	void Shutdown();
	DX10Model* GetModelByName(std::string);
	void SetID3D10Device(ID3D10Device* device);
private:
	std::unordered_map<std::string,IntrusivePtr<DX10Model> > m_modelMap;
	ID3D10Device* m_device;
};