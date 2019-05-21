#pragma once
#include "../../DEFINITIONS.h"
#include "../../OBJ_Loader.h"

class Obstacle
{
public:
	Obstacle(float xx, float yy, float zz, float scale);
	~Obstacle();
	void setTexture(unsigned int texID);
	void drawObstacle();

public:
	objl::Loader floor;
	float posX;
	float posY;
	float posZ;
	unsigned int texture;
	float scale;
};

