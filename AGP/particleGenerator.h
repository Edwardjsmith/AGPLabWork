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
	enum particleEffects { RAINBOW_FOUNTAIN, RAIN };
	particleEffects effects;
	particleGenerator(ID3D11Device* device, ID3D11DeviceContext* context, float rotation, particleEffects type);
	~particleGenerator();

	int createParticle();
	void Draw(XMMATRIX* view, XMMATRIX* projection, XMFLOAT3* cameraPos, float timeNow, float deltaTime);
	void drawOne(Particle* part, XMMATRIX* view, XMMATRIX* projection, XMFLOAT3* cameraPos);
	

private:

	std::list<Particle*> m_free;
	std::list<Particle*> m_active;

	int numOfParticles = 10000;

	ID3D11RasterizerState* m_pRasterSolid = 0;
	ID3D11RasterizerState* m_pRasterParticle = 0;
	ID3D11Buffer*		m_pVertexBuffer;
	PARTICLE_CONSTANT_BUFFER particle_cb_values;

	float m_timePrevious;
	float m_untilParticle;
	float RandomZeroToOne();
	float RandomNegOneToPosOne();
	float RandomPosOnScreen(float rangeMin, float rangeMax);
	float m_age;

	float m_scale;

	bool m_isActive;

	std::list<Particle*>::iterator it;//iteration list for pointing to the correct particle in the list
};

