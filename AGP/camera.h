#pragma once
#include <d3d11.h>
#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include<xnamath.h>

class camera
{
public:

	camera(float x, float y, float z);
	~camera();

	XMVECTOR getPositionXM() const; //Return camera pos
	XMFLOAT3 getPos() const;

	void setPos(float x, float y, float z);
	void setPos(const XMFLOAT3& value);


	//Get basic camera vectors
	XMVECTOR getRightXM() const;
	XMVECTOR getUpXM() const;
	XMVECTOR getLookXM() const;

	XMFLOAT3 getRight() const;
	XMFLOAT3 getUp() const;
	XMFLOAT3 getLook() const;

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
	void setLens(float fovY, float aspect, float zn, float zf);

	//Define camera space via lookat
	void lookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp);
	void lookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up);

	//View/proj matrices
	XMMATRIX View() const;
	XMMATRIX Proj() const;
	XMMATRIX viewProj() const;

	//Strafe and walk
	void strafe(float direction);
	void walk(float direction);

	//Rotate cam
	void Pitch(float angle);
	void RotateY(float angle);

	void updateViewMatrix();

private:
	XMFLOAT3 mPosition;
	XMFLOAT3 mRight;
	XMFLOAT3 mUp;
	XMFLOAT3 mLook;


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
	XMFLOAT4X4 mView;
	XMFLOAT4X4 mProj;

};

