#include "Arm.h"



Arm::Arm(float x, float y, float z)
{
	posX = x;
	posY = y;
	posZ = z;
}


Arm::~Arm()
{
}

void Arm::setTexture(unsigned int smokID)
{
	smok = smokID;
	GLfloat cl[] = { 1, 1, 0.1f };
	GLfloat cn[] = { posX + 35, posY + 70, posZ + 35 };

	skillet.setParams(cl, cn, 10, 5, 0, 1);

	cl[0] = 1;
	cl[1] = 0.7f;
	cl[2] = 0;

	cn[0] -= 6;
	cn[2] = posZ + 90;

	bush.setParams(cl, cn, 5, 12, 0, 1);

	a[0] = posX + 30;
	a[1] = posY + 65;
	a[2] = posZ + 40;

	b[0] = posX + 40;
	b[1] = posY + 65;
	b[2] = posZ + 40;

	c[0] = posX + 40;
	c[1] = posY + 75;
	c[2] = posZ + 40;

	d[0] = posX + 30;
	d[1] = posY + 75;
	d[2] = posZ + 40;

	basis.setParams(cl, a, b, c, d, 50, smok);

	a[1] -= 5;
	a[2] += 45;

	b[1] -= 5;
	b[2] += 45;

	c[1] -= 5;
	c[2] += 45;

	d[1] -= 5;
	d[2] += 45;

	forearm.setParams(cl, a, b, c, d, 25, smok);
}

void Arm::drawArm()
{
	skillet.drawCylinder(-90, 0, 1, 0);
	bush.drawCylinder(0, 0, 0, 0);
	basis.drawCuboid(0, 0, 0, 0);
	forearm.drawCuboid(-90, 1, 0, 0);
}
