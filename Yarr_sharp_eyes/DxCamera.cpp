#include "DxCamera.h"

DxCamera::DxCamera()
	: Camera()
{
}

DxCamera::DxCamera(const DxCamera& other)
	: Camera(other)
{
}

DxCamera::~DxCamera()
{
}

void DxCamera::SetPosition(float x, float y, float z)
{
	Camera::SetPosition(x, y, z);
}

void DxCamera::SetRotation(float x, float y, float z)
{
	Camera::SetRotation(x, y, z);
}

D3DXVECTOR3 DxCamera::GetPosition()
{
	return D3DXVECTOR3(m_posX, m_posY, m_posZ);
}

D3DXVECTOR3 DxCamera::GetRotation()
{
	return D3DXVECTOR3(m_rotX, m_rotY, m_rotZ);
}

void DxCamera::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}

D3DXMATRIX* DxCamera::SetViewMatrix()
{
	return &m_viewMatrix;
}

