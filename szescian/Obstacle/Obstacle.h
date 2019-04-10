#pragma once
#include "../../DEFINITIONS.h"
#include "../../OBJ_Loader.h"

class Obstacle
{
public:
	Obstacle(float xx, float yy, float zz, float scale);
	~Obstacle();

public:
	objl::Loader floor;
};

