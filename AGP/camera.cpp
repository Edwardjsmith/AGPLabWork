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

	m_dx = m_camera_rotation - m_x;
	m_dz = m_camera_rotation - m_z;
}

void camera::Forward(float distanceMoved)
{
	m_x += (m_dx * distanceMoved);
	m_z += (m_dz * distanceMoved);
}

void camera::Up(float distance)
{
	m_y += distance;
}

XMMATRIX camera::GetViewMatrix()
{
	m_position = { m_x, m_y, m_z };
	m_lookat = { m_dx, m_y, m_dz };
	m_up = { 0, m_y, 0 };


	return XMMatrixLookAtLH(m_position, m_lookat, m_up);
}


