#pragma once
#include "../../DEFINITIONS.h"

class Cone
{
public:
	Cone(GLfloat * colour, GLfloat * cen, GLfloat r, GLfloat hh);
	Cone();
	~Cone();
	void setParams(GLfloat * colour, GLfloat * cen, GLfloat r, GLfloat hh);
	void drawCone(GLfloat rot, GLfloat xdg, GLfloat ydg, GLfloat zdg);
	GLfloat color[3];
	GLfloat center[3];
	GLfloat radius;
	GLfloat height;
	GLfloat angle;
};

