#pragma once
#include "entity.h"
class enemy :
	public entity
{
public:
	enemy(ID3D11Device* device, ID3D11DeviceContext* context, float rotation, float scaleX, float scaleY, float scaleZ, entity* Target);
	~enemy();

	entity* mTarget;

	void moveToTarget(float speed);
	void Update(timer* time, float gravityScale, bool touchingFloor, float moveSpeed);

	void Draw(XMMATRIX * view, XMMATRIX * projection, entity * Target);
};

