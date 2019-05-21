#pragma once
#include "../../../../DEFINITIONS.h"
#include "../../../Cuboid/Cuboid.h"

class Frame : public Cuboid
{
public:
	Frame(float x, float y, float z);
	~Frame();
	GLfloat a[3];
	GLfloat b[3];
	GLfloat c[3];
	GLfloat d[3];
	GLfloat color[3];
	float getPositionX();
	float getPositionY();
	float getPositionZ();
	void drawFrame();
	float posX;
	float posY;
	float posZ;
};

