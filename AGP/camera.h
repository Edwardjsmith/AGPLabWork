#pragma once
#include <d3d11.h>
#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include<xnamath.h>

class camera
{
public:

	camera(float x, float y, float z, float rotation);
	~camera();

private:

	float m_x, m_y, m_z, m_dx, m_dz, m_camera_rotation;
	XMVECTOR m_position, m_lookat, m_up;

};

