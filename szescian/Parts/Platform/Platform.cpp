#include "Platform.h"



Platform::Platform(float x, float y, float z)
	: arm(x, y, z)
{
	a[0] = x + 30;
	a[1] = y + 40;
	a[2] = z + 40;

	b[0] = x + 30;
	b[1] = y + 40;
	b[2] = z + 75;

	c[0] = x + 30;
	c[1] = y + 70;
	c[2] = z + 70;

	d[0] = x + 30;
	d[1] = y + 90;
	d[2] = z + 40;

	color[0] = 0.8f;
	color[1] = 0.3f;
	color[2] = 0.3f;

	LeftFront.setParams(color, a, b, c, d, 5);
	LeftFront.drawCuboid(0, 0, 0, 0);

	a[2] = z - 5;
	b[2] = z + 30;
	c[1] = y + 90;
	c[2] = z + 30;
	d[1] = y + 70;
	d[2] = z;
	RightFront.setParams(color, a, b, c, d, 5);
	RightFront.drawCuboid(0, 0, 0, 0);

	a[1] = y - 20;
	a[2] = z - 13;
	b[1] = y;
	b[2] = z + 30;
	c[1] = y + 35;
	c[2] = z + 30;
	d[1] = y + 35;
	d[2] = z - 5.5f;
	RightBack.setParams(color, a, b, c, d, 5);
	RightBack.drawCuboid(0, 0, 0, 0);

	a[2] = z + 83;
	b[2] = z + 40;
	c[2] = z + 40;
	d[2] = z + 75.5f;
	LeftBack.setParams(color, a, b, c, d, 5);
	LeftBack.drawCuboid(0, 0, 0, 0);
}


Platform::~Platform()
{
}
