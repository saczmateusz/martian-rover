#pragma once
#include "../../definitions.h"

class Axle
{
public:
	Axle(float x, float y, float z, char side);
	~Axle();

private:
	GLfloat angle = 0, x, y, z, r = 3;
};

