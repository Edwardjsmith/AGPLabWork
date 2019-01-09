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
	void Strafe(float distance);
	void Up(float movement);
	XMVECTOR getLook();
private:
	Model* m_Target;
	XMVECTOR m_offset;

};

