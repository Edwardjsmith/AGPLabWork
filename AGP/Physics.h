#pragma once
#include "Model.h"

class entity;
class Physics
{
public:
	
	~Physics();

	static Physics* getInstance();

	bool checkSphereCollision(Model* modelA, Model* modelB);
	bool checkAABB(Model* modelA, Model* modelB);


private:
	Physics();
	static Physics* instance;
};

