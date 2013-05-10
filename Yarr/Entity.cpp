#include "Entity.h"

Entity::Entity()
{
	m_posX = 0.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;
	m_entityName = "Nameless One";
}

Entity::Entity(std::string entityName, float x, float y, float z)
{
	m_entityName = entityName;
	m_posX = x;
	m_posY = y;
	m_posZ = z;
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

std::string Entity::GetName() const 
{
	return m_entityName;
}