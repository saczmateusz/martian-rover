#pragma once
#include "../../../DEFINITIONS.h"
#include "../../Cuboid/Cuboid.h"
#include "../Arm/Arm.h"
#include "../../Cone/Cone.h"


class Platform
{
public:
	Platform(float x, float y, float z, unsigned int texID, unsigned int smokID);
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
	Arm arm;
	Cone engine;
	Cylinder engineCore;
	Cone thrust;
};

