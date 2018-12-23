#pragma once
#include "camera.h"
class thirdPersonCamera :
	public Camera
{
public:
	thirdPersonCamera(float x, float y, float z, float c_rot, float pitch, Model* target);
	~thirdPersonCamera();

	XMMATRIX GetViewMatrix();
	void Strafe(float distance);
	void Up(float movement);
private:
	Model* m_Target;
	XMVECTOR m_offset;

};

