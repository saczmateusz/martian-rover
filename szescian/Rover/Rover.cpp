#include "Rover.h"



Rover::Rover(float x, float y, float z) :
	chassis(x, y, z),
	platform(x, y, z)
{
	GLfloat cl[] = { 0.3f, 0.3f, 0.3f };
	GLfloat cn[] = { x, y + 10, z + 10 };
	
	for (int j = 0; j < 3; ++j)
	{
		Cylinder wheel(cl, cn, 10, 10, 0, 1);
		wheels.push_back(wheel);
		cn[1] += 30;
	}
	cn[1] = y + 10;
	cn[0] += 60;
	for (int j = 0; j < 3; ++j)
	{
		Cylinder wheel(cl, cn, 10, 10, 0, 1);
		wheels.push_back(wheel);
		cn[1] += 30;
	}
}


Rover::~Rover()
{
}

void Rover::drawRover()
{
	for (auto &wheel : wheels)
	{
		wheel.drawCylinder(0, 0, 0, 0);
	}
	chassis.drawChassis();
	platform.drawPlatform();
}

void Rover::setTextures(unsigned int texID, unsigned int smokID)
{
	platform.setTextures(texID, smokID);
}
