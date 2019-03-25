#include "Platform.h"



Platform::Platform(float x, float y, float z) :
	LeftFront(),
	RightFront(),
	LeftBack(),
	RightBack()
{
	GLfloat a[3] = { x + 30, y + 40, z + 40 };
	GLfloat b[3] = { x + 30, y + 40, z + 75 };
	GLfloat c[3] = { x + 30, y + 70, z + 70 };
	GLfloat d[3] = { x + 30, y + 90, z + 40 };
	LeftFront.drawCuboid(a, b, c, d, 5);

	a[2] = z - 5;
	b[2] = z + 30;
	c[1] = y + 90;
	c[2] = z + 30;
	d[1] = y + 70;
	d[2] = z;

	RightFront.drawCuboid(a, b, c, d, 5);

	a[1] = y - 20;
	a[2] = z - 13;
	b[1] = y;
	b[2] = z + 30;
	c[1] = y + 35;
	c[2] = z + 30;
	d[1] = y + 35;
	d[2] = z - 5.5f;

	RightBack.drawCuboid(a, b, c, d, 5);

	a[2] = z + 83;
	b[2] = z + 40;
	c[2] = z + 40;
	d[2] = z + 75.5f;

	LeftBack.drawCuboid(a, b, c, d, 5);
}


Platform::~Platform()
{
}
