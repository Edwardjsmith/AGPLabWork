#include "camera.h"




camera::camera(float x, float y, float z, float angle)
{
	mAngle = angle;
	mPosition = XMVectorSet(x, y, z, 0);

	m_dx = sin(mAngle * (XM_PI / 180));
	m_dz = cos(mAngle * (XM_PI / 180));

	mLook = XMVectorSet(x + m_dx, y, z + m_dz, 0);
	mUp = XMVectorSet(0, 1, 0, 0);

	mView = XMMatrixLookAtLH(mPosition, mLook, mUp);
}

camera::~camera()
{
}


XMVECTOR camera::getPos()
{
	return mPosition;
}

void camera::setPos(float x, float y, float z)
{
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
}

void camera::setPos(const XMVECTOR & value)
{
	mPosition += value;
}

XMVECTOR camera::getRightXM() const
{
	return mRight;
}

XMVECTOR camera::getUpXM() const
{
	return mUp;
}

XMVECTOR camera::getLookXM() const
{
	return mLook;
}

XMVECTOR camera::getRight()
{
	return mRight;
}

XMVECTOR camera::getUp()
{
	return mUp;
}

XMVECTOR camera::getLook()
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
}

float camera::getnearWindowWidth() const
{
	return mAspect * mNearWindowHeight;
}

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
	
XMMATRIX camera::View(XMVECTOR pos, XMVECTOR look, XMVECTOR up) 
{
	mPosition = pos;
	mLook = look;
	mUp = up;

	return mView = XMMatrixLookAtLH(mPosition, mLook, mUp);
}

XMMATRIX camera::Proj(float FovY, float aspect, float nearZ, float farZ)
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





