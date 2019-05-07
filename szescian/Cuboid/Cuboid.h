#pragma once
#include "../../DEFINITIONS.h"

class Cuboid
{
public:
	Cuboid(GLfloat * colour, GLfloat * aa, GLfloat * bb, GLfloat * cc, GLfloat * dd, GLfloat hh, unsigned int texID);
	Cuboid();
	~Cuboid();
	void drawCuboid(GLfloat rot, GLfloat xdg, GLfloat ydg, GLfloat zdg);
	void setParams(GLfloat * colour, GLfloat * aa, GLfloat * bb, GLfloat * cc, GLfloat * dd, GLfloat hh, unsigned int texID);

public:
	GLfloat color[3];
	GLfloat a[3];
	GLfloat b[3];
	GLfloat c[3];
	GLfloat d[3];
	GLfloat height;
	unsigned int tex;
};

