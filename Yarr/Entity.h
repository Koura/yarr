#pragma once

#include "CRefCounted.h"
#include <cmath>
#include <string>

struct POSITION
{
	float x;
	float y;
	float z;
};

class Entity : public CRefCounted
{
public:
	Entity();
	Entity(std::string, float, float, float);
	Entity(const Entity&);
	~Entity();
	POSITION GetPosition();
	void SetPosition(float, float, float);
	std::string GetName() const;
private:
	float m_posX, m_posY, m_posZ;
	std::string m_entityName;
};

