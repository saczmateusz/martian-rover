#pragma once
#include "../../DEFINITIONS.h"
#include "../../OBJ_Loader.h"

class Terrain
{
public:
	Terrain(unsigned int texID);
	~Terrain();

public:
	objl::Loader floor;
};

