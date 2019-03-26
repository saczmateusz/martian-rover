#pragma once
#include "../../Cylinder/Cylinder.h"
#include "../../Cuboid/Cuboid.h"

class Arm
{
public:
	Arm(float x, float y, float z);
	~Arm();
	Cylinder skillet;
	Cylinder bush;
	Cuboid basis;
	Cuboid forearm;
	GLfloat a[3];
	GLfloat b[3];
	GLfloat c[3];
	GLfloat d[3];
};

