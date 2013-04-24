#include "Camera.h"

Camera::Camera()
{
	m_posX = 0.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;
	m_rotX = 0.0f;
	m_rotY = 0.0f;
	m_rotZ = 0.0f;
}

Camera::Camera(const Camera& other)
{
}

Camera::~Camera()
{
}

void Camera::SetPosition(float x, float y, float z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;
	return;
}

void Camera::SetRotation(float x, float y, float z)
{
	m_rotX = x;
	m_rotY = y;
	m_rotZ = z;
	return;
}