#include "Arm.h"



Arm::Arm(float x, float y, float z, unsigned int smokID)
{
	GLfloat cl[] = { 1, 1, 0.1f };
	GLfloat cn[] = { x + 35, y + 70, z + 35};

	skillet.setParams(cl, cn, 10, 5, 0, 1);
	skillet.drawCylinder(-90, 0, 1, 0);

	cl[0] = 1;
	cl[1] = 0.7f;
	cl[2] = 0;

	cn[0] -= 6;
	cn[2] = z + 90;

	bush.setParams(cl, cn, 5, 12, 0, 1);
	bush.drawCylinder(0, 0, 0, 0);


	a[0] = x + 30;
	a[1] = y + 65;
	a[2] = z + 40;

	b[0] = x + 40;
	b[1] = y + 65;
	b[2] = z + 40;

	c[0] = x + 40;
	c[1] = y + 75;
	c[2] = z + 40;

	d[0] = x + 30;
	d[1] = y + 75;
	d[2] = z + 40;

	basis.setParams(cl, a, b, c, d, 50, smokID);
	basis.drawCuboid(0, 0, 0, 0);

	a[1] -= 5;
	a[2] += 45;

	b[1] -= 5;
	b[2] += 45;

	c[1] -= 5;
	c[2] += 45;

	d[1] -= 5;
	d[2] += 45;

	forearm.setParams(cl, a, b, c, d, 25, smokID);
	forearm.drawCuboid(-90, 1, 0, 0);
}


Arm::~Arm()
{
}
