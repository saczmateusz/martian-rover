#pragma once
#include "../definitions.h"

class Cuboid
{
public:
	Cuboid(GLfloat * a, GLfloat * b, GLfloat * c, GLfloat * d, GLfloat h);
	Cuboid();
	~Cuboid();
	void drawCuboid(GLfloat * a, GLfloat * b, GLfloat * c, GLfloat * d, GLfloat h);
};

