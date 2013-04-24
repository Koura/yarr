#pragma once

class Camera
{
public:
	Camera();
	Camera(const Camera&);
	~Camera();

	void SetRotation(float, float, float);
	void SetPosition(float, float, float);
	
private:
	float m_posX, m_posY, m_posZ;
	float m_rotX, m_rotY, m_rotZ;
};
