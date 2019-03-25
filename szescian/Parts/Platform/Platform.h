#pragma once
#include "../../definitions.h"
#include "../../Cuboid/Cuboid.h"

class Platform
{
public:
	Platform(float x, float y, float z);
	~Platform();
private:
	Cuboid LeftFront;
	Cuboid RightFront;
	Cuboid LeftBack;
	Cuboid RightBack;
};

