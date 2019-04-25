#pragma once
#include "../definitions.h"

class Cylinder
{
public:
	Cylinder(GLfloat * colour, GLfloat * cen, GLfloat r, GLfloat hh, GLfloat grad = 0, int s = 1);
	Cylinder();
	~Cylinder();
	void setParams(GLfloat * colour, GLfloat * cen, GLfloat r, GLfloat hh, GLfloat grad, int s);
	void drawCylinder(GLfloat rot, GLfloat xdg, GLfloat ydg, GLfloat zdg);

public:
	GLfloat color[3];
	GLfloat center[3];
	GLfloat radius;
	GLfloat height;
	GLfloat gradient;
	GLfloat angle;
	int side;
};

