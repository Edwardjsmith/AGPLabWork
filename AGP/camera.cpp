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

void camera::Rotate(float numberOfDegrees)
{
	m_camera_rotation += numberOfDegrees;

	
}

void camera::Forward(float distanceMoved)
{

}

void camera::Up(float distance)
{
	m_y += distance;
}

XMMATRIX camera::GetViewMatrix()
{
	


	return XMMATRIX();
}


