#pragma once


<<<<<<< HEAD
#include "d3d11.h"
=======
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
>>>>>>> parent of b87047e... Backup

#include "xnamath.h"
#include "math.h"



<<<<<<< HEAD
class Camera
{
public:
=======
	//View/proj matrices
	XMMATRIX View() const;
	XMMATRIX Proj(float FovY, float aspect, float nearZ, float farZ) const;

	//Strafe and walk
	void strafe(float direction);
	void walk(float direction);
>>>>>>> parent of b87047e... Backup

	Camera(float x, float y, float z, float c_rot, float pitch);
	void Rotate(float deg_change);
	void Pitch(float deg_change);
	void Forward(float movement);
	void Up(float movement);
	void Strafe(float distance);
	XMMATRIX GetViewMatrix();
	~Camera();

private:
<<<<<<< HEAD
	float m_x, m_y, m_z, m_dx, m_dy, m_dz, m_camera_rotation, m_camera_pitch, m_ax, m_az;
	XMVECTOR m_position, m_lookat, m_up;
=======
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

>>>>>>> parent of b87047e... Backup
};


