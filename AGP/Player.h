#pragma once
#include "thirdPersonCamera.h"
#include "entity.h"
#include "input.h"
class Player :
	public entity
{
public:
	Player(ID3D11Device* device, ID3D11DeviceContext* context, float rotation);
	~Player();

	void Draw(XMMATRIX* view, XMMATRIX* projection, XMFLOAT3* cameraPos);

	void Update() override;

private:

	Camera* Cam;
	input* Input;
};

