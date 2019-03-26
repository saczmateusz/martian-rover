#pragma once
#include "../definitions.h"

class Cuboid
{
public:
	Cuboid(GLfloat * colour, GLfloat * aa, GLfloat * bb, GLfloat * cc, GLfloat * dd, GLfloat hh);
	Cuboid();
	~Cuboid();
	void drawCuboid();
	void setParams(GLfloat * colour, GLfloat * aa, GLfloat * bb, GLfloat * cc, GLfloat * dd, GLfloat hh);

public:
	GLfloat color[3];
	GLfloat a[3];
	GLfloat b[3];
	GLfloat c[3];
	GLfloat d[3];
	GLfloat height;
};

