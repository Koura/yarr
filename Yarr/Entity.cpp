#include "Entity.h"

Entity::Entity()
{
	m_posX = 0.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;
}

Entity::Entity(const Entity& other)
{
}

Entity::~Entity()
{
}

void Entity::SetPosition(float x, float y, float z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;
	return;
}

POSITION Entity::GetPosition()
{
	POSITION pos;
	pos.x = m_posX;
	pos.y = m_posY;
	pos.z = m_posZ;
	return pos;
}