#include "Rover.h"



Rover::Rover(float x, float y, float z) :
	chassis(x, y, z),
	platform(x, y, z)
{
	GLfloat cl[] = { 0.3f, 0.3f, 0.3f };
	GLfloat cn[] = { x + 10, y + 10, z };
	
	for (int j = 0; j < 3; ++j)
	{
		Cylinder wheel(cl, cn, 10, 10, 0, 1);
		wheels.push_back(wheel);
		cn[1] += 30;
	}
	cn[1] = y + 10;
	cn[2] += 60;
	for (int j = 0; j < 3; ++j)
	{
		Cylinder wheel(cl, cn, 10, 10, 0, 1);
		wheels.push_back(wheel);
		cn[1] += 30;
	}

	for (auto &wheel : wheels)
	{
		wheel.drawCylinder(0, 0, 0, 0);
	}
}


Rover::~Rover()
{
}
