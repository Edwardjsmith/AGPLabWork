#pragma once
#include <d3d11.h>

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include <xnamath.h>
#include <math.h>

class Camera
{
public:

	Camera(float x, float y, float z, float c_rot, float pitch, float screenW, float screenH);
	void Rotate(float deg_change);
	void Pitch(float deg_change);
	void Forward(float movement);
	void Up(float movement);
	void Strafe(float distance);
	XMMATRIX GetViewMatrix();
	~Camera();

	float getX();
	float getY();
	float getZ();

	void updateView();
	void setPos(float x, float y, float z);

	XMMATRIX getProjection();
	XMMATRIX getView();

	XMFLOAT3 getPos();

	float getRotSpeed();
	void setLookat(float x, float y, float z);
protected:


	XMMATRIX projection, view;

	float m_x, m_y, m_z, m_dx, m_dy, m_dz, m_camera_rotation, m_camera_pitch;

	XMVECTOR m_position, m_up, m_lookat, m_rotation, m_right;

	float mAngle;
	float dx, dy, dz;

	float screenWidth, screenheight;
	float rotationSpeed = 10;
	
};


