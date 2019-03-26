#include "Platform.h"



Platform::Platform(float x, float y, float z) :
	LeftFront(),
	RightFront(),
	LeftBack(),
	RightBack()
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

	LeftFront.setParams(a, b, c, d, 5);
	LeftFront.setColor(color);
	LeftFront.drawCuboid();

	a[2] = z - 5;
	b[2] = z + 30;
	c[1] = y + 90;
	c[2] = z + 30;
	d[1] = y + 70;
	d[2] = z;
	RightFront.setParams(a, b, c, d, 5);
	RightFront.setColor(color);
	RightFront.drawCuboid();

	a[1] = y - 20;
	a[2] = z - 13;
	b[1] = y;
	b[2] = z + 30;
	c[1] = y + 35;
	c[2] = z + 30;
	d[1] = y + 35;
	d[2] = z - 5.5f;
	RightBack.setParams(a, b, c, d, 5);
	RightBack.setColor(color);
	RightBack.drawCuboid();

	a[2] = z + 83;
	b[2] = z + 40;
	c[2] = z + 40;
	d[2] = z + 75.5f;
	LeftBack.setParams(a, b, c, d, 5);
	LeftBack.setColor(color);
	LeftBack.drawCuboid();
}


Platform::~Platform()
{
}
