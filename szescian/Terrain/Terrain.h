#pragma once
#include "../../DEFINITIONS.h"
#include "../../OBJ_Loader.h"

class Terrain
{
public:
	Terrain();
	~Terrain();

public:
	objl::Loader floor;
};

