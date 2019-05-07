#include "Platform.h"



Platform::Platform(float x, float y, float z, unsigned int texID, unsigned int smokID)
	: arm(x, y, z, smokID)
{
	a[0] = x + 40;
	a[1] = y + 40;
	a[2] = z + 30;

	b[0] = x + 75;
	b[1] = y + 40;
	b[2] = z + 30;

	c[0] = x + 70;
	c[1] = y + 70;
	c[2] = z + 30;

	d[0] = x + 40;
	d[1] = y + 90;
	d[2] = z + 30;

	color[0] = 0.8f;
	color[1] = 0.3f;
	color[2] = 0.3f;

	LeftFront.setParams(color, a, b, c, d, 5, texID);
	LeftFront.drawCuboid(0, 0, 0, 0);

	a[0] = x - 5;
	b[0] = x + 30;
	c[1] = y + 90;
	c[0] = x + 30;
	d[1] = y + 70;
	d[0] = x;
	RightFront.setParams(color, a, b, c, d, 5, texID);
	RightFront.drawCuboid(0, 0, 0, 0);

	a[1] = y - 20;
	a[0] = x - 13;
	b[1] = y;
	b[0] = x + 30;
	c[1] = y + 35;
	c[0] = x + 30;
	d[1] = y + 35;
	d[0] = x - 5.5f;
	RightBack.setParams(color, a, b, c, d, 5, texID);
	RightBack.drawCuboid(0, 0, 0, 0);

	a[0] = x + 83;
	b[0] = x + 40;
	c[0] = x + 40;
	d[0] = x + 75.5f;
	LeftBack.setParams(color, a, b, c, d, 5, texID);
	LeftBack.drawCuboid(0, 0, 0, 0);

	GLfloat cl[] = { 0.5f, 0.5f, 0.5f };
	GLfloat cn[] = { x + 35, y + 40, z + 41 };

	engine.setParams(cl, cn, 15, 30);
	engine.drawCone(-90, 1, 0, 0);

	cn[1] = y + 10;

	engineCore.setParams(cl, cn, 15, 25, 0, 1);
	engineCore.drawCylinder(-90, 0, 0, 1);

	cl[0] = 1;
	cl[1] = 0.4f;
	cl[2] = 0.3f;

	cn[1] = y - 55;

	thrust.setParams(cl, cn, 10, 40);
	thrust.drawCone(90, 1, 0, 0);
}


Platform::~Platform()
{
}
