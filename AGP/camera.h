#pragma once
#include "d3d11.h"
#include "xnamath.h"
#include "math.h"

class Camera
{
public:

	Camera(float x, float y, float z, float c_rot, float pitch);
	void Rotate(float deg_change);
	void Pitch(float deg_change);
	void Forward(float movement);
	void Up(float movement);
	void Strafe(float distance);
	XMMATRIX GetViewMatrix();
	~Camera();

private:

	float m_x, m_y, m_z, m_dx, m_dy, m_dz, m_camera_rotation, m_camera_pitch, m_ax, m_az;

	XMVECTOR m_position, m_right, m_up, m_lookat, m_rotation;
	float mAngle;
	float dx, dy, dz;
};


