#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Entity.h"
#include "Camera.h"
#include <D3DX10math.h>


class Camera: public Camera
{
public:
	Camera();
	Camera(const Camera&);
	~Camera();

	void SetRotation(float, float, float);
	D3DXVECTOR3 GetPosition();
	void SetPosition(float, float, float);
	
	D3DXVECTOR3 GetRotation();
	void GetViewMatrix(D3DXMATRIX&);
	D3DXMATRIX* SetViewMatrix();
	
private:
	float m_posX, m_posY, m_posZ;
	float m_rotX, m_rotY, m_rotZ;
	D3DXMATRIX m_viewMatrix;
};

#endif