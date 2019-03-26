#pragma once
#include "../../definitions.h"
#include "../../Cuboid/Cuboid.h"


class Platform
{
public:
	Platform(float x, float y, float z);
	~Platform();
private:
	GLfloat a[3];
	GLfloat b[3];
	GLfloat c[3];
	GLfloat d[3];
	GLfloat color[3];
	Cuboid LeftFront;
	Cuboid RightFront;
	Cuboid LeftBack;
	Cuboid RightBack;
};

