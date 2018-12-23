#pragma once
#include "objfilemodel.h"


struct MODEL_CONSTANT_BUFFER
{
	XMMATRIX WorldViewProjection; //64 bytes (4 x 4 x4)
};

class Model
{
public:
	Model(ID3D11Device* device, ID3D11DeviceContext* context, float rotation);
	~Model();

	virtual HRESULT LoadObjModel(const char* filename, const char* textureName);
	virtual void Draw(XMMATRIX* view, XMMATRIX* projection, XMFLOAT3* cameraPos);

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


	void Rotate(float deg_change);
	void Pitch(float deg_change);
	void Forward(float movement);
	void Up(float movement);
	void Strafe(float distance);
	XMVECTOR getLook();

	XMVECTOR getPos();

	void setLook(XMVECTOR look);

protected:

	ID3D11Device*			m_pD3DDevice;
	ID3D11DeviceContext*	m_pImmediateContext;

	ObjFileModel*		m_pObject;
	ID3D11VertexShader*	m_pVShader;
	ID3D11PixelShader*	m_pPShader;
	ID3D11InputLayout*	m_pInputLayout;
	ID3D11Buffer*		m_pConstantBuffer;

	float			m_x, m_y, m_z, m_dx, m_dy, m_dz;
	float			m_xAngle, m_yAngle, m_zAngle;
	float			m_scale;
	float			m_model_rotation;

	void setShaders();

	MODEL_CONSTANT_BUFFER model_cb_values;

	string shaderType;
	string shaderFile;
	string shaderVersion;

	ID3D11ShaderResourceView* m_pTexture;
	ID3D11SamplerState* m_pSampler;

	XMVECTOR m_position, m_up, m_lookat, m_rotation, m_right;


};

