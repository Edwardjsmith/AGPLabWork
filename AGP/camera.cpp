#include "camera.h"




camera::camera(float x, float y, float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
	updateViewMatrix();
}

camera::~camera()
{
}


XMVECTOR camera::getPos() const
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
	mPosition.x += value.x;
	mPosition.y += value.y;
	mPosition.z += value.z;
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

	XMMATRIX P = XMMatrixPerspectiveFovLH(mFovY, mAspect, mNearZ, mFarZ);


	return P;
}

void camera::lookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp)
{
	XMVECTOR L = XMVector3Normalize(XMVectorSubtract(target, pos));
	XMVECTOR R = XMVector3Normalize(XMVector3Cross(worldUp, L));
	XMVECTOR U = XMVector3Cross(L, R);

	XMStoreFloat3(&mPosition, pos);
	XMStoreFloat3(&mLook, L);
	XMStoreFloat3(&mRight, R);
	XMStoreFloat3(&mUp, U);
}

void camera::lookAt(const XMFLOAT3 & pos, const XMFLOAT3 & target, const XMFLOAT3 & up)
{
	XMVECTOR P = XMLoadFloat3(&pos);
	XMVECTOR T = XMLoadFloat3(&target);
	XMVECTOR U = XMLoadFloat3(&up);

	lookAt(P, T, U);

}

XMMATRIX camera::View() const
{
	XMMATRIX view = XMLoadFloat4x4(&mView);
	return view;
}

XMMATRIX camera::Proj() const
{
	XMMATRIX proj = XMMatrixLookAtLH(mPosition, mLook, mUp);
	return proj;
}

XMMATRIX camera::viewProj() const
{
	XMMATRIX viewproj = XMLoadFloat4x4(&mView) * XMLoadFloat4x4(&mProj);

	return viewproj;
}

void camera::strafe(float direction)
{
	XMVECTOR replicate = XMVectorReplicate(direction);
	XMVECTOR right = XMLoadFloat3(&mRight);
	XMVECTOR pos = XMLoadFloat3(&mPosition);

	XMStoreFloat3(&mPosition, XMVectorMultiplyAdd(replicate, right, pos));
}

void camera::walk(float direction)
{
	XMVECTOR replicate = XMVectorReplicate(direction);
	XMVECTOR look = XMLoadFloat3(&mLook);
	XMVECTOR pos = XMLoadFloat3(&mPosition);

	XMStoreFloat3(&mPosition, XMVectorMultiplyAdd(replicate, look, pos));
}

void camera::Pitch(float angle)
{
	XMMATRIX rot = XMMatrixRotationAxis(XMLoadFloat3(&mRight), angle);

	XMStoreFloat3(&mUp, XMVector3TransformNormal(XMLoadFloat3(&mUp), rot));
	XMStoreFloat3(&mLook, XMVector3TransformNormal(XMLoadFloat3(&mLook), rot));
}

void camera::RotateY(float angle)
{
	XMMATRIX rot = XMMatrixRotationY(angle);

	XMStoreFloat3(&mRight, XMVector3TransformNormal(XMLoadFloat3(&mRight), rot));

	XMStoreFloat3(&mUp, XMVector3TransformNormal(XMLoadFloat3(&mUp), rot));
	XMStoreFloat3(&mLook, XMVector3TransformNormal(XMLoadFloat3(&mLook), rot));
}

void camera::updateViewMatrix()
{
	XMVECTOR right = XMLoadFloat3(&mRight);
	XMVECTOR up = XMLoadFloat3(&mUp);
	XMVECTOR look = XMLoadFloat3(&mLook);
	XMVECTOR pos = XMLoadFloat3(&mPosition);

	//Make look a vector unit in length
	look = XMVector3Normalize(look);

	up = XMVector3Normalize(XMVector3Cross(look, right));

	right = XMVector3Cross(up, look);

	float x = -XMVectorGetX(XMVector3Dot(pos, right));
	float y = -XMVectorGetX(XMVector3Dot(pos, up));
	float z = -XMVectorGetX(XMVector3Dot(pos, look));

	XMStoreFloat3(&mRight, right);
	XMStoreFloat3(&mUp, up);
	XMStoreFloat3(&mLook, look);

	mView(0, 0) = mRight.x;
	mView(1, 0) = mRight.y;
	mView(2, 0) = mRight.z;
	mView(3, 0) = x;

	mView(0, 1) = mUp.x;
	mView(1, 1) = mUp.y;
	mView(2, 1) = mUp.z;
	mView(3, 1) = y;

	mView(0, 2) = mLook.x;
	mView(1, 2) = mLook.y;
	mView(2, 2) = mLook.z;
	mView(3, 2) = z;

	mView(0, 3) = 0.0f;
	mView(1, 3) = 0.0f;
	mView(2, 3) = 0.0f;
	mView(3, 3) = 1.0f;
}



