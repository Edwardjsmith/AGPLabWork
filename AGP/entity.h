#pragma once
#include "Model.h"
#include "timer.h"
#include "Grid.h"


class entity :
	public Model
{

	friend class Grid;
public:
	entity(ID3D11Device* device, ID3D11DeviceContext* context, float rotation, Grid* grid);
	~entity();

	virtual void Update(timer time);

	float getSpeed();

	void Rotate(float deg_change);
	void Pitch(float deg_change);
	void Forward(float movement, Grid* grid);
	void Up(float movement, Grid* grid);
	void Strafe(float distance, Grid* grid);
	
	float oldXPos;
	float oldYPos;
	float oldZPos;

protected:
	float mSpeed = 1.0f;
	float rotSpeed = 1.0f;

	entity* prev;
	entity* next;


	
};

