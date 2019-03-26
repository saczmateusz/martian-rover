#include "Chassis.h"



Chassis::Chassis(float x, float y, float z) :
	frame(x, y, z)
{
	GLfloat cl[] = { 0.3f, 0.3f, 0.8f };
	GLfloat cn[] = { x + 10, y + 10, z + 10};
	
	for (int j = 0; j < 3; ++j)
	{
		Cylinder axle(cl, cn, 2, 15, 15, 1);
		axles.push_back(axle);
		cn[1] += 30;
	}
	cn[1] = y + 10;
	cn[2] += 50;
	for (int j = 0; j < 3; ++j)
	{
		Cylinder axle(cl, cn, 2, 15, 15, -1);
		axles.push_back(axle);
		cn[1] += 30;
	}

	for (auto &axle : axles)
	{
		axle.drawCylinder();
	}
}


Chassis::~Chassis()
{
	
}
