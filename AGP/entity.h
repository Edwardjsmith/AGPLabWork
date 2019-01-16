#pragma once
#include "Model.h"
#include "timer.h"

class entity :
	public Model
{

	friend class Grid;
public:
	entity(ID3D11Device* device, ID3D11DeviceContext* context, float rotation, float scaleX, float scaleY, float scaleZ);
	~entity();

	virtual void Update(timer* time, float gravityScale, bool touchingFloor);

	float getSpeed();
	float getRotSpeed();
	float getStrafeSpeed();

	void Rotate(float deg_change);
	void Pitch(float deg_change);
	void Forward(float movement);
	void Up(float movement);
	void Strafe(float distance);

	void knockBack(float knockbackForce, float targetX, float targetZ);
	
	float oldXPos;
	float oldYPos;
	float oldZPos;

	void setStartPos(float x, float y, float z);

	float knockBackforce = 500;
	bool touchingFloor;
	float startX, startY, startZ;
protected:
	float mSpeed = 1.0f;
	float mStrafe = 1.0f;
	float mRotSpeed = 1.0f;
	float mGravityScale;

	
	
};

