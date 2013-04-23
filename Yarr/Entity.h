#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <cmath>

struct POSITION
{
	float x;
	float y;
	float z;
};

class Entity
{
public:
	Entity();
	Entity(const Entity&);
	~Entity();
	POSITION GetPosition();
	void SetPosition(float, float, float);

private:
	float m_posX, m_posY, m_posZ;
};

#endif