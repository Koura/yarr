#pragma once
#include <string>

class ModelFactory
{
public:
	ModelFactory(){};
	ModelFactory(const ModelFactory&){};
	~ModelFactory(){};
	virtual void Shutdown() = 0;
	virtual void CreateModel(std::string) = 0;
};