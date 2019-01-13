#pragma once
#include "entity.h"
#include "input.h"

class Player :
	public entity
{
public:
	
	Player(ID3D11Device* device, ID3D11DeviceContext* context, float rotation, float scaleX, float scaleY, float scaleZ);
	~Player();

	void Draw(XMMATRIX* view, XMMATRIX* projection);
	void Jump(float jumpForce);

	
private:
	input* Input;
};

