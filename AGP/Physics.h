#pragma once


class entity;
class Physics
{
public:
	
	~Physics();

	static Physics* getInstance();

	bool checkCollision(entity* modelA, entity* modelB);

private:
	Physics();
	static Physics* instance;
};

