#pragma once
#include "Model.h"
#include "camera.h"
class thirdPersonCamera :
	public Camera
{
public:
	thirdPersonCamera(float x, float y, float z, float c_rot, float pitch, float screenW, float screenH, Model* target);
	~thirdPersonCamera();

	XMMATRIX GetViewMatrix();
	void Orbit(float distance);
	void Up(float movement);
	XMVECTOR getLook();

	void setRotationXZ(float rotation);
	void setRotationY(float rotation);

private:
	Model* m_Target;
	XMVECTOR m_offset;
	XMVECTOR m_distanceFromTarget;

	float rotationXZ = 0;
	float rotationY = 0;
};

