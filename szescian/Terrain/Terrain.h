#pragma once
#include "../../DEFINITIONS.h"
#include "../../OBJ_Loader.h"

class Terrain
{
public:
	Terrain();
	~Terrain();
	void drawTerrain();
	void setTexture(unsigned int texID);

public:
	objl::Loader floor;
	unsigned int texture;

};

