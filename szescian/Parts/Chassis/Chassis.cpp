#include "Chassis.h"



Chassis::Chassis(float x, float y, float z) :
	frame(x, y, z)
{
	posX = x;
	posY = y;
	posZ = z;

	GLfloat cl[] = { 0.3f, 0.3f, 0.8f };
	GLfloat cn[] = { posX + 10, posY + 10, posZ + 10 };

	for (int j = 0; j < 3; ++j)
	{
		Cylinder axle(cl, cn, 3, 15, 15, 1);
		axles.push_back(axle);
		cn[1] += 30;
	}
	cn[1] = posY + 10;
	cn[0] += 50;
	for (int j = 0; j < 3; ++j)
	{
		Cylinder axle(cl, cn, 3, 15, 15, -1);
		axles.push_back(axle);
		cn[1] += 30;
	}
}


Chassis::~Chassis()
{
	
}


void Chassis::drawChassis()
{
	for (auto &axle : axles)
	{
		axle.drawCylinder(0, 0, 0, 0);
	}
}
