#pragma once
#include "../../definitions.h"
#include "../../../Cuboid/Cuboid.h"

class Frame : public Cuboid
{
public:
	Frame(float x, float y, float z);
	~Frame();
	void setBackX(float a, float b);
	void setBackY(float a, float b);
	void setBackZ(float a, float b);
	float getBackX();
	float getBackY();
	float getBackZ();
	GLfloat a[3];
	GLfloat b[3];
	GLfloat c[3];
	GLfloat d[3];
	GLfloat color[3];
	float backX;
	float backY;
	float backZ;
};

