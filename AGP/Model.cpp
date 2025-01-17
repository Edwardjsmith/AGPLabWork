#include "Model.h"
#include <iostream>





Model::Model(ID3D11Device * device, ID3D11DeviceContext * context, float rotation, float scaleX, float ScaleY, float scaleZ)
{
	m_pD3DDevice = device;
	m_pImmediateContext = context;

	mScaleX = scaleX;
	mScaleY = ScaleY;
	mScaleZ = scaleZ;

	m_x = m_y = m_z = 0.0f;
	m_xAngle = m_yAngle = m_zAngle = 0.0f;

	m_model_rotation = rotation;

	m_dx = sin(m_model_rotation * (XM_PI / 180));
	m_dz = cos(m_model_rotation * (XM_PI / 180));

	shaderFile = "model_shaders.hlsl";
	shaderType = "Model";

	m_pTexture = nullptr;
	m_pSampler = nullptr;

	getBoundingSphereWorldSpacePosition();
}

Model::~Model()
{

	if (m_pPShader) m_pPShader->Release();
	if (m_pVShader) m_pVShader->Release();
	if (m_pObject) delete m_pObject;
	if (m_pInputLayout) m_pInputLayout->Release();
	if (m_pTexture) m_pTexture->Release();
	if (m_pSampler) m_pSampler->Release();
	if (m_pConstantBuffer) m_pConstantBuffer->Release();
}

HRESULT Model::LoadObjModel(const char * filename)
{
	HRESULT hr = S_OK;
	m_pObject = new ObjFileModel((char*)filename, m_pD3DDevice, m_pImmediateContext);

	if (m_pObject->filename == "FILE NOT LOADED") return S_FALSE;

	ID3DBlob *VS, *PS, *error;

	hr = D3DX11CompileFromFile(shaderFile.c_str(), 0, 0, (shaderType + "VS").c_str(), "vs_4_0", 0, 0, 0, &VS, &error, 0);

	if (error != 0)//Check for shader compilation error
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr))//Don't fail if error is just a warning
		{
			DXTRACE_MSG("Failed model VS");
			return hr;
		}
	}

	hr = D3DX11CompileFromFile(shaderFile.c_str(), 0, 0, (shaderType + "PS").c_str() , "ps_4_0", 0, 0, 0, &PS, &error, 0);

	if (error != 0)//Check for shader compilation error
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr))//Don't fail if error is just a warning
		{
			DXTRACE_MSG("Failed model PS");
			return hr;
		}
	}

	//Create shader objects
	hr = m_pD3DDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_pVShader);
	if (FAILED(hr))
	{
		DXTRACE_MSG("Failed to create model vertex shader");
		return hr;
	}

	hr = m_pD3DDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pPShader);
	if (FAILED(hr))
	{
		DXTRACE_MSG("Failed to create model pixel shader");
		return hr;
	}

	m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);
	m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);

	//Create and set the input layout object
	D3D11_INPUT_ELEMENT_DESC iedesc[] =
	{
		//Be very careful setting the correct dxgi format and D3D version
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		//NOTE the spelling of COLOR. Again, be careful setting the correct dxgi format (using A32) and correct D3D version
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	hr = m_pD3DDevice->CreateInputLayout(iedesc, ARRAYSIZE(iedesc), VS->GetBufferPointer(), VS->GetBufferSize(), &m_pInputLayout);
	if (FAILED(hr))
	{
		DXTRACE_MSG("Failed to create model input layer");
		return hr;
	}

	m_pImmediateContext->IASetInputLayout(m_pInputLayout);

	//Set up Const buffer
	D3D11_BUFFER_DESC constant_buffer_desc;
	ZeroMemory(&constant_buffer_desc, sizeof(constant_buffer_desc));

	constant_buffer_desc.Usage = D3D11_USAGE_DEFAULT; //Can use Update subresource to update
	constant_buffer_desc.ByteWidth = constantBufferByteWidth; //Set size, must be multiple of 16;
	constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; //Use as const buffer

	hr = m_pD3DDevice->CreateBuffer(&constant_buffer_desc, NULL, &m_pConstantBuffer);

	if (FAILED(hr))//Return an error code if failed
	{
		DXTRACE_MSG("Failed model const buffer");
		return hr;
	}


	calcCentrePoint();

	return S_OK;
}

void Model::Draw(XMMATRIX* view, XMMATRIX* projection)
{
	//m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pImmediateContext->PSSetSamplers(0, 1, &m_pSampler);
	m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTexture);

	directionOfLight = XMVectorSet(0.25f, 0.5f, -1.0f, 0.0f);
	lightColour = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	ambientColour = XMVectorSet(0.2f, 0.2f, 0.2f, 1.0f);

	XMMATRIX world = XMMatrixScaling(mScaleX, mScaleY,mScaleZ);
	world *= XMMatrixRotationX(XMConvertToRadians(m_xAngle));
	world *= XMMatrixRotationY(XMConvertToRadians(m_yAngle));
	world *= XMMatrixRotationZ(XMConvertToRadians(m_zAngle));
	world *= XMMatrixTranslation(m_x, m_y, m_z);

	XMMATRIX transpose = XMMatrixTranspose(world);

	model_cb_values.WorldViewProjection = world * (*view) * (*projection);
	model_cb_values.lightColour = lightColour;
	model_cb_values.ambientColour = ambientColour;
	model_cb_values.directionOfLight = XMVector3Transform(directionOfLight, transpose);
	model_cb_values.directionOfLight = XMVector3Normalize(model_cb_values.directionOfLight);

	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, 0, &model_cb_values, 0, 0);

	setShaders();

	m_pObject->Draw();
}

void Model::setPosition(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;

	//m_position = XMVectorSet(m_x, m_y, m_z, 0);
}

void Model::setX(float x)
{
	m_x += x;
}

float Model::getX()
{
	return m_x;
}

void Model::setY(float y)
{
	m_y += y;
}

float Model::getY()
{
	return m_y;
}

void Model::setZ(float z)
{
	m_z += z;
}

float Model::getZ()
{
	return m_z;
}



void Model::setXRotation(float value)
{
}

float Model::getXRotation()
{
	return m_xAngle;
}

void Model::setYRotation(float value)
{
}

float Model::getYRotation()
{
	return m_yAngle;
}



void Model::setZRotation(float value)
{
}

float Model::getZRotation()
{
	return m_zAngle;
}

float Model::getScaleX()
{
	return mScaleX;
}



float Model::getScaleY()
{
	return mScaleY;
}

float Model::getScaleZ()
{
	return mScaleZ;
}

XMVECTOR Model::getPos()
{
	return m_position = XMVectorSet(m_x, m_y, m_z, 0);;
}

XMFLOAT3 Model::getPosFloat3()
{
	return XMFLOAT3(m_x, m_y, m_z);
}

void Model::setLook(XMVECTOR look)
{
	m_lookat = look;
}


HRESULT Model::setSampler()
{
	HRESULT hr;
	D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = m_pD3DDevice->CreateSamplerState(&sampler_desc, &m_pSampler);
	if (FAILED(hr))
	{
		DXTRACE_MSG("Failed to create sampler");
		return hr;
	}

	return S_OK;
}

HRESULT Model::setTexture(const char* filename)
{
	HRESULT hr;
	hr = D3DX11CreateShaderResourceViewFromFile(m_pD3DDevice, filename, NULL, NULL, &m_pTexture, NULL);

	if (FAILED(hr))
	{
		DXTRACE_MSG("Failed to create texture");
		return hr;
	}

	return S_OK;
}

void Model::setShaders()
{
	m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);
	m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);
	m_pImmediateContext->IASetInputLayout(m_pInputLayout);
}


XMVECTOR Model::getBoundingSphereWorldSpacePosition()
{
	
		XMMATRIX world = XMMatrixScaling(mScaleX, mScaleY, mScaleZ);
		world *= XMMatrixRotationX(XMConvertToRadians(m_xAngle));
		world *= XMMatrixRotationY(XMConvertToRadians(m_yAngle));
		world *= XMMatrixRotationZ(XMConvertToRadians(m_zAngle));
		world *= XMMatrixTranslation(m_x, m_y, m_z);
		XMVECTOR offset = XMVectorSet(m_boundingSphereCentreX, m_boundingSphereCentreY, m_boundingSphereCentreZ, 0);

		return offset = XMVector3Transform(offset, world);
}
float Model::getSphereRadius()
{
	return m_boundingSphereRadius * mScaleY;
}


void Model::Cleanup()
{

}

void Model::calcCentrePoint()
{
	for (int i = 0; i < m_pObject->numverts; i++)
	{
		XMVECTOR centre = XMLoadFloat3(&m_pObject->vertices[i].Pos);
		vertMin = XMVectorMin(vertMin, centre);
		vertMax = XMVectorMax(vertMax, centre);
	}

	m_boundingSphereCentreX = vertMax.x - vertMin.x;
	m_boundingSphereCentreY = vertMax.y - vertMin.y;
	m_boundingSphereCentreZ = vertMax.z - vertMin.z;

	m_boundingSphereRadius = (sqrt((m_boundingSphereCentreX * m_boundingSphereCentreX) + (m_boundingSphereCentreY * m_boundingSphereCentreY) + (m_boundingSphereCentreZ * m_boundingSphereCentreZ)));
}
