#pragma once
#include <d3d11.h>
#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include<xnamath.h>


class camera
{
public:

	camera(float x, float y, float z, float angle);
	~camera();

	XMVECTOR getPos() const;

	void setPos(float x, float y, float z);
	void setPos(const XMVECTOR& value);


	//Get basic camera vectors
	XMVECTOR getRightXM() const;
	XMVECTOR getUpXM() const;
	XMVECTOR getLookXM() const;

	XMVECTOR getRight() const;
	XMVECTOR getUp() const;
	XMVECTOR getLook() const;

	//Get frustum properties
	float getNearZ() const;
	float getFarZ() const;
	float getAspect() const;
	float getFOVY() const;
	float getFOVX() const;
	float getFOVZ() const;

	//get near and far plane dimensions in view space coords
	float getnearWindowWidth() const;
	float getnearWindowHeight() const;
	float getfarWindowWidth() const;
	float getfarWindowHeight() const;
	
	//set frustum
	XMMATRIX setLens(float fovY, float aspect, float zn, float zf);

	//Define camera space via lookat
	void lookAt(XMVECTOR pos, XMVECTOR target, XMVECTOR worldUp);


	//View/proj matrices
	XMMATRIX View() const;
	XMMATRIX Proj(float FovY, float aspect, float nearZ, float farZ) const;

	//Strafe and walk
	void strafe(float direction);
	void walk(float direction);

	//Rotate cam
	void Pitch(float angle);
	void RotateY(float angle);

private:
	XMVECTOR mPosition, mRight, mUp, mLook, mRotation;
	float mAngle;
	float dx, dy, dz;


	//Cach frustum props
	float mNearZ;
	float mFarZ;
	float mAspect;
	float mFovY;
	float mFovX;
	float mFovZ;
	float mNearWindowHeight;
	float mFarWindowHeight;
	float mNearWindowWidth;
	float mFarWindowWidth;

	//Cache view proj matrices
	XMMATRIX mView;
	XMMATRIX mProj;

};

