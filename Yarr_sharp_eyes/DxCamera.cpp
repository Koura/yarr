#include "DxCamera.h"

DxCamera::DxCamera()
{
	m_posX = 0.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;
	m_rotX = 0.0f;
	m_rotY = 0.0f;
	m_rotZ = 0.0f;
}

DxCamera::DxCamera(const DxCamera& other)
{
}

DxCamera::~DxCamera()
{
}

void DxCamera::SetPosition(float x, float y, float z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;
	return;
}

void DxCamera::SetRotation(float x, float y, float z)
{
	m_rotX = x;
	m_rotY = y;
	m_rotZ = z;
	return;
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

void DxCamera::Render()
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw,pitch,roll;
	D3DXMATRIX rotationMatrix;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
	position.x = m_posX;
	position.y = m_posY;
	position.z = m_posZ;
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;
	pitch = m_rotX * 0.0174532925f;
	yaw   = m_rotY * 0.0174532925f;
	roll  = m_rotZ * 0.0174532925f;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);
	lookAt = position + lookAt;
	D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up);
	return;
}

