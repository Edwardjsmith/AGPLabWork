#pragma once
#include "Model.h"
class CubeMap :
	public Model
{
public:
	CubeMap(ID3D11Device* device, ID3D11DeviceContext* context, float scaleX, float Scaley, float scaleZ);
	~CubeMap();

	void Draw(XMMATRIX* view, XMMATRIX* projection);
	HRESULT LoadObjModel(const char* filename, const char* textureName) override;

private:
	ID3D11RasterizerState* m_pRasterSolid = 0;
	ID3D11RasterizerState* m_pRasterSkyBox = 0;
	ID3D11DepthStencilState* m_pDepthWriteSolid = 0;
	ID3D11DepthStencilState* m_pDepthWriteSkyBox = 0;

	

};



