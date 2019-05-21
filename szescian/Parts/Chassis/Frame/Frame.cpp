#include "Frame.h"



Frame::Frame(float x, float y, float z)
{
	posX = x;
	posY = y;
	posZ = z;
	color[0] = 0.0f;
	color[1] = 1.0f;
	color[2] = 0.0f;

	a[0] = posX + 25;
	a[1] = posY;
	a[2] = posZ + 20;

	b[0] = posX + 45;
	b[1] = posY;
	b[2] = posZ + 20;

	c[0] = posX + 45;
	c[1] = posY + 80;
	c[2] = posZ + 20;

	d[0] = posX + 25;
	d[1] = posY + 80;
	d[2] = posZ + 20;

	setParams(color, a, b, c, d, 10, 0);
}


Frame::~Frame()
{
}

float Frame::getPositionX()
{
	return posX;
}

float Frame::getPositionY()
{
	return posY;
}

float Frame::getPositionZ()
{
	return posZ;
}

void Frame::drawFrame()
{
	drawCuboid(0, 0, 0, 0);
}
