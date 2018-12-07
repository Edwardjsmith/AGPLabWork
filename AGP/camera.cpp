#include "camera.h"

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT



Camera::Camera(float x, float y, float z, float c_rot, float pitch)
{
<<<<<<< HEAD
	m_x = x;
	m_y = y;
	m_z = z;
	m_camera_rotation = c_rot;
	m_camera_pitch = pitch;
	m_dx = sin(m_camera_rotation * (XM_PI / 180));
	m_dz = cos(m_camera_rotation * (XM_PI / 180));
	m_dy = m_camera_pitch * (XM_PI / 180);
=======
	mAngle = angle;
	mPosition = XMVectorSet(x, y, z, 0);

	dx = sin(mAngle * (XM_PI / 180));
	dz = cos(mAngle * (XM_PI / 180));

	mLook = XMVectorSet(x + dx, y, z + dz, 0);
	mUp = XMVectorSet(0, 1, 0, 0);

	mView = XMMatrixLookAtLH(mPosition, mLook, mUp);
>>>>>>> parent of b87047e... Backup
}
void Camera::Rotate(float deg_change) {
	m_camera_rotation += deg_change;
	m_dx = sin(m_camera_rotation * (XM_PI / 180));
	m_dz = cos(m_camera_rotation * (XM_PI / 180));
	m_ax = sin((m_camera_rotation + 90) * (XM_PI / 180));
	m_az = cos((m_camera_rotation + 90) * (XM_PI / 180));
}
<<<<<<< HEAD
void Camera::Pitch(float deg_change) {
	m_camera_pitch += deg_change;
	m_dy = m_camera_pitch * (XM_PI / 180);
=======


XMVECTOR camera::getPos() const
{
	return mPosition;
>>>>>>> parent of b87047e... Backup
}
void Camera::Forward(float movement) {
	m_x += movement * m_dx;
	m_y += movement * m_dy;
	m_z += movement * m_dz;
}
void Camera::Up(float movement) {
	m_y += movement * m_dy;
}
void Camera::Strafe(float movement)
{
	/*Hint: Use the cross product calculation here first to calculate the direction*/
	m_x += m_ax * movement;
	m_z += m_az * movement;
}

<<<<<<< HEAD
XMMATRIX Camera::GetViewMatrix() {
	m_position = XMVectorSet(m_x, m_y, m_z, 0.0);
	m_lookat = XMVectorSet(m_x + m_dx, m_y + m_dy, m_z + m_dz, 0.0);
	//m_position = XMVectorSet(0.0, 0.0, -0.5, 0.0);
	//m_lookat = XMVectorSet(0.0, 0.0, -0.4, 0.0);
	m_up = XMVectorSet(0.0, 1.0, 0.0, 0.0);
	return XMMatrixLookAtLH(m_position, m_lookat, m_up);
=======
XMVECTOR camera::getLookXM() const
{
	return mLook;
}

XMVECTOR camera::getRight() const
{
	return mRight;
}

XMVECTOR camera::getUp() const
{
	return mUp;
}

XMVECTOR camera::getLook() const
{
	return mLook;
}

float camera::getNearZ() const
{
	return mNearZ;
}

float camera::getFarZ() const
{
	return mFarZ;
}

float camera::getAspect() const
{
	return mAspect;
}

float camera::getFOVY() const
{
	return mFovY;
}

float camera::getFOVX() const
{
	float halfWidth = 0.5f * getnearWindowWidth();

	return 2.0f * atan(halfWidth / mNearZ);
}

float camera::getFOVZ() const
{
	return mFovZ;
>>>>>>> parent of b87047e... Backup
}

Camera::~Camera()
{
}
<<<<<<< HEAD
=======

float camera::getnearWindowHeight() const
{
	return mNearWindowHeight;
}

float camera::getfarWindowWidth() const
{
	return mAspect * mFarWindowHeight;
}

float camera::getfarWindowHeight() const
{
	return mFarWindowHeight;
}

XMMATRIX camera::setLens(float fovY, float aspect, float zn, float zf)
{
	mFovY = fovY;
	mAspect = aspect;
	mNearZ = zn;
	mFarZ = zf;

	mNearWindowHeight = 2.0f * mNearZ * tanf(0.5f * mFovY);
	mFarWindowHeight = 2.0f * mFarZ * tanf(0.5f * mFovY);

	return Proj(fovY, aspect, zn, zf);
}

void camera::lookAt(XMVECTOR pos, XMVECTOR target, XMVECTOR worldUp)
{
	mLook = XMVectorSet(target.x, target.y, target.z, target.w);

	//mLook = mLook + pos;
}
	
XMMATRIX camera::View() const
{
	return mView;
}

XMMATRIX camera::Proj(float FovY, float aspect, float nearZ, float farZ) const
{
	return XMMatrixPerspectiveFovLH(mFovY, mAspect, mNearZ, mFarZ);
}

void camera::strafe(float direction)
{
	mPosition += mRight * direction;
}

void camera::walk(float direction)
{
	mPosition += mLook * direction;
}

void camera::Pitch(float angle)
{
	/*XMMATRIX rot = XMMatrixRotationAxis(XMLoadFloat3(&mRight), angle);

	XMStoreFloat3(&mUp, XMVector3TransformNormal(XMLoadFloat3(&mUp), rot));
	XMStoreFloat3(&mLook, XMVector3TransformNormal(XMLoadFloat3(&mLook), rot));*/
}

void camera::RotateY(float angle)
{
	/*XMMATRIX rot = XMMatrixRotationY(angle);

	XMStoreFloat3(&mRight, XMVector3TransformNormal(XMLoadFloat3(&mRight), rot));

	XMStoreFloat3(&mUp, XMVector3TransformNormal(XMLoadFloat3(&mUp), rot));
	XMStoreFloat3(&mLook, XMVector3TransformNormal(XMLoadFloat3(&mLook), rot));*/
}





>>>>>>> parent of b87047e... Backup
