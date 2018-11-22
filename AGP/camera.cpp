#include "camera.h"




camera::camera(float x, float y, float z, float rotation)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_camera_rotation = rotation;
}

camera::~camera()
{
}
