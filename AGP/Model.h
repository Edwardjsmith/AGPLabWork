#pragma once
#include "objfilemodel.h"
class Model
{
public:
	Model(ID3D11Device* device, ID3D11DeviceContext* context);
	~Model();

	virtual HRESULT LoadObjModel(const char* filename);
	virtual void Draw(XMMATRIX* view, XMMATRIX* projection);

	void setPosition(float x, float y, float z);

	void setX(float x);
	float getX();

	void setY(float y);
	float getY();

	void setZ(float z);
	float getZ();

	void setScale(float value);
	float getScale();

	void setXRotation(float value);
	float getXRotation();

	void setYRotation(float value);
	float getYRotation();

	void setZRotation(float value);
	float getZRotation();

protected:

	ID3D11Device*			m_pD3DDevice;
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

