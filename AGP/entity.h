#pragma once
#include "Model.h"
class entity :
	public Model
{
public:
	entity(ID3D11Device* device, ID3D11DeviceContext* context, float rotation);
	~entity();

	virtual void Update();

};

