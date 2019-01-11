#pragma once
#include "entity.h"
class enemy :
	public entity
{
public:
	enemy(ID3D11Device* device, ID3D11DeviceContext* context, float rotation, entity* Target);
	~enemy();

	entity* m_target;

	void moveToTarget(float speed);

	void Draw(XMMATRIX* view, XMMATRIX* projection, entity* Target);
};

