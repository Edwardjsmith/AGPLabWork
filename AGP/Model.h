#pragma once
#include "objfilemodel.h"
class Model
{
public:
	Model(ID3D11Device* device, ID3D11DeviceContext* context);
	~Model();

	HRESULT LoadObjModel(const char* filename);

private:
	ID3D11Device*		m_pD3DDevice;
	ID3D11DeviceContext*	m_pImmediateContext;

	ObjFileModel*		m_pObject;
	ID3D11VertexShader*	m_pVShader;
	ID3D11PixelShader*	m_pPShader;
	ID3D11InputLayout*	m_pInputLayout;
	ID3D11Buffer*		m_pConstantBuffer;

	float			m_x, m_y, m_z;
	float			m_xAngle, m_yAngle, m_zAngle;
	float			m_scale;
};

