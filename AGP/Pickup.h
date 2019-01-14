#pragma once
#include "Model.h"
class Pickup :
	public Model
{
public:
	Pickup(ID3D11Device * device, ID3D11DeviceContext * context, float rotation, float scaleX, float ScaleY, float scaleZ);
	~Pickup();

	void Draw(XMMATRIX* view, XMMATRIX* projection);

	struct PICKUP_CONSTANT_BUFFER
	{
		XMMATRIX WorldView; //16
		XMMATRIX WorldViewProjection; //64 bytes (4 x 4 x4)
		XMVECTOR directionOfLight; //16
		XMVECTOR lightColour; //16
		XMVECTOR ambientColour; //16

		//128
	};
};

