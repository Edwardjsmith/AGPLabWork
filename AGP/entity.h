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

	void Rotate(float deg_change);
	void Pitch(float deg_change);
	void Forward(float movement);
	void Up(float movement);
	void Strafe(float distance);
	
	float oldXPos;
	float oldYPos;
	float oldZPos;

	XMVECTOR startPos;
	bool touchingFloor;

protected:
	float mSpeed = 1.0f;
	float rotSpeed = 1.0f;
	float mGravityScale;
	
};

