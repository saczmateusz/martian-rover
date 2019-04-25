#include "Frame.h"



Frame::Frame(float x, float y, float z)
{
	//w domysle bedzie podawane przez konstruktor
	
	color[0] = 0.0f;
	color[1] = 1.0f;
	color[2] = 0.0f;

	a[0] = x + 25;
	a[1] = y;
	a[2] = z + 20;

	b[0] = x + 45;
	b[1] = y;
	b[2] = z + 20;

	c[0] = x + 45;
	c[1] = y + 80;
	c[2] = z + 20;

	d[0] = x + 25;
	d[1] = y + 80;
	d[2] = z + 20;


	setParams(color, a, b, c, d, 10);
	drawCuboid(0, 0, 0, 0);
	
	setBackX(a[0], b[0]);
	setBackY(a[1], b[1]);
	setBackZ(a[2], b[2]);
}


Frame::~Frame()
{
}

void Frame::setBackX(float a, float b)
{
	this->backX = (a + b) / 2;
}

void Frame::setBackY(float a, float b)
{
	this->backY = (a + b) / 2;
}

void Frame::setBackZ(float a, float b)
{
	this->backZ = (a + b) / 2;
}

float Frame::getBackX()
{
	return this->backX;
}

float Frame::getBackY()
{
	return this->backY;
}

float Frame::getBackZ()
{
	return this->backZ;
}




