#pragma once
#include "entity.h"
#include "input.h"
class Player :
	public entity
{
public:
	Player(ID3D11Device* device, ID3D11DeviceContext* context, float , Grid* grid);
	~Player();

	void Draw(XMMATRIX* view, XMMATRIX* projection, XMFLOAT3* cameraPos);

	void Update(timer time) override;

private:

	input* Input;
};

