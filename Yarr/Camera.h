#pragma once

class Camera
{
public:
	Camera();
	Camera(const Camera&);
	~Camera();

    virtual void SetRotation(float, float, float);
	virtual void SetPosition(float, float, float);
	
protected:
	float m_posX, m_posY, m_posZ;
	float m_rotX, m_rotY, m_rotZ;
};
