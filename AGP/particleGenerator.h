#pragma once
#include "Model.h"
#include <list>

struct Particle
{
	float gravity;
	XMFLOAT3 position;
	XMFLOAT3 velocity;
	XMFLOAT4 color;
	float age;
};

struct PARTICLE_CONSTANT_BUFFER
{
	XMMATRIX WorldViewProjection; //64 bytes (4 x 4 x4)
	XMFLOAT4 color; //16 bytes
};

class particleGenerator : public Model
{
public:
	particleGenerator(ID3D11Device* device, ID3D11DeviceContext* context, float rotation);
	~particleGenerator();

	int createParticle();
	void Draw(XMMATRIX* view, XMMATRIX* projection, XMFLOAT3* cameraPos, float timeNow, float dt);
	void drawOne(Particle* part, XMMATRIX* view, XMMATRIX* projection, XMFLOAT3* cameraPos);
	

private:

	std::list<Particle*> m_free;
	std::list<Particle*> m_active;

	int numOfParticles = 100;

	ID3D11RasterizerState* m_pRasterSolid = 0;
	ID3D11RasterizerState* m_pRasterParticle = 0;
	ID3D11Buffer*		m_pVertexBuffer;
	PARTICLE_CONSTANT_BUFFER particle_cb_values;

	float m_timePrevious;
	float m_untilParticle;
	float randomZeroToOne();
	float RandomNegOneToPosOne();
	float m_age;

	enum particleEffects {RAINBOW_FOUNTAIN};
	particleEffects effects;

	bool m_isActive;

	std::list<Particle*>::iterator it;//iteration list for pointing to the correct particle in the list
};

