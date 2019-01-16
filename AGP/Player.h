#pragma once
#include "entity.h"

class Player :
	public entity
{
public:
	
	Player(ID3D11Device* device, ID3D11DeviceContext* context, float rotation, float scaleX, float scaleY, float scaleZ);
	~Player();

	void Jump(float jumpForce);
	void Forward(float movement, float targetX, float targetZ);
	
private:

	
};

