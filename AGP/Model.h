#pragma once
#include "objfilemodel.h"


struct MODEL_CONSTANT_BUFFER
{
	XMMATRIX WorldViewProjection; //64 bytes (4 x 4 x4)
	XMVECTOR directionOfLight; //16
	XMVECTOR lightColour; //16
	XMVECTOR ambientColour; //16

	//148 total
};

class Model
{
public:
	Model(ID3D11Device* device, ID3D11DeviceContext* context, float rotation, float scaleX, float Scaley, float scaleZ);
	~Model();

	virtual HRESULT LoadObjModel(const char* filename, const char* textureName);
	virtual void Draw(XMMATRIX* view, XMMATRIX* projection);

	void setPosition(float x, float y, float z);

	void setX(float x);
	float getX();

	void setY(float y);
	float getY();

	void setZ(float z);
	float getZ();



	void setXRotation(float value);
	float getXRotation();

	void setYRotation(float value);
	float getYRotation();

	void setZRotation(float value);
	float getZRotation();

	float getScaleX();
	float getScaleY();
	float getScaleZ();


	XMVECTOR getPos();
	XMFLOAT3 getPosFloat3();

	void setLook(XMVECTOR look);


	float m_boundingSphereCentreX, m_boundingSphereCentreY, m_boundingSphereCentreZ, m_boundingSphereRadius;

	XMVECTOR getBoundingSphereWorldSpacePosition();

	float getSphereRadius();


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
	float			m_model_rotation;

	XMVECTOR vertMin, vertMax;
	void setShaders();


	void calcCentrePoint();

	MODEL_CONSTANT_BUFFER model_cb_values;

	

	string shaderType;
	string shaderFile;
	string shaderVersion;

	ID3D11ShaderResourceView* m_pTexture;
	ID3D11SamplerState* m_pSampler;

	XMVECTOR m_position, m_up, m_lookat, m_rotation, m_right;


	XMVECTOR directionOfLight; //16
	XMVECTOR lightColour; //16
	XMVECTOR ambientColour; //16

	float mScaleX, mScaleY, mScaleZ;

};

