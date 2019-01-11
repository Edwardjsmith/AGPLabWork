
#pragma once
#include "Physics.h"
#include <string>


//#include "soundManager.h"

class entity;


class Grid
{


public:
	Grid();
	~Grid();




	void add(entity* Entity);

	void handleCell(entity* Entity);

	void moveEntity(entity* Entity, float x, float y, float z);

	//Store old position values to revert to on collision

	float oldX;
	float oldY;

private:

	static const int CELL_SIZE = 10;
	static const int NUM_CELLS = 10;


	const float collisionDist = 0.1f;
	entity* cells[NUM_CELLS][NUM_CELLS][NUM_CELLS];


};