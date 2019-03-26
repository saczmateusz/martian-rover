#pragma once
#include "../definitions.h"

class Cuboid
{
public:
	Cuboid(GLfloat * a, GLfloat * b, GLfloat * c, GLfloat * d, GLfloat h);
	Cuboid();
	~Cuboid();
	void drawCuboid();
	void setParams(GLfloat * aa, GLfloat * bb, GLfloat * cc, GLfloat * dd, GLfloat hh);
	void setColor(GLfloat * c);
	GLfloat a[3];
	GLfloat b[3];
	GLfloat c[3];
	GLfloat d[3];
	GLfloat color[3];
	GLfloat h;
};

