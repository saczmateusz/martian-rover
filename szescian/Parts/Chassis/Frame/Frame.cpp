#include "Frame.h"



Frame::Frame(float x, float y, float z)
{
	//w domysle bedzie podawane przez konstruktor
	
	color[0] = 0.0f;
	color[1] = 1.0f;
	color[2] = 0.0f;

	a[0] = x + 20;
	a[1] = y;
	a[2] = z + 25;

	b[0] = x + 20;
	b[1] = y;
	b[2] = z + 45;

	c[0] = x + 20;
	c[1] = y + 80;
	c[2] = z + 45;

	d[0] = x + 20;
	d[1] = y + 80;
	d[2] = z + 25;


	setParams(color, a, b, c, d, 10);
	drawCuboid();
}


Frame::~Frame()
{
}
