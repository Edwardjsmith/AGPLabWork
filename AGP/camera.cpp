#include "camera.h"


Camera::Camera(float x, float y, float z, float c_rot, float pitch)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_camera_rotation = c_rot;
	m_camera_pitch = pitch;
	m_dx = sin(m_camera_rotation * (XM_PI / 180));
	m_dz = cos(m_camera_rotation * (XM_PI / 180));
	m_dy = m_camera_pitch * (XM_PI / 180);
}
void Camera::Rotate(float deg_change) 
{
	m_camera_rotation += deg_change;
	m_dx = sin(m_camera_rotation * (XM_PI / 180));
	m_dz = cos(m_camera_rotation * (XM_PI / 180));
}

void Camera::Pitch(float deg_change) 
{
	m_camera_pitch += deg_change;
	m_dy = m_camera_pitch * (XM_PI / 180);
}

void Camera::Forward(float movement) 
{
	m_x += movement * m_dx;
	m_y += movement * m_dy;
	m_z += movement * m_dz;
}
void Camera::Up(float movement) 
{
	m_y += m_up.y * movement;
	m_z += m_up.z * movement;
}
void Camera::Strafe(float movement)
{
	/*Hint: Use the cross product calculation here first to calculate the direction*/
	//m_x += m_ax * movement;
	//m_z += m_az * movement;
	
	m_right = XMVector3Cross(m_lookat - m_position, m_up);

	m_x += m_right.x * movement;
	m_z += m_right.z * movement;
	
}

XMMATRIX Camera::GetViewMatrix()
{
	m_position = XMVectorSet(m_x, m_y, m_z, 0.0);
	m_lookat = XMVectorSet(m_x + m_dx, m_y + m_dy, m_z + m_dz, 0.0);
	m_up = XMVectorSet(0.0, 1.0, 0.0, 0.0);
	return XMMatrixLookAtLH(m_position, m_lookat, m_up);
}

Camera::~Camera()
{
}

float Camera::getX()
{
	return m_x;
}

float Camera::getY()
{
	return m_y;
}

float Camera::getZ()
{
	return m_z;
}

XMFLOAT3 Camera::getPos()
{
	return XMFLOAT3(m_x, m_y, m_z);
}



