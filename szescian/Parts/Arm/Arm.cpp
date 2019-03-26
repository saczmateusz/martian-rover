#include "Arm.h"



Arm::Arm(float x, float y, float z)
{
	GLfloat cl[] = { 0.1f, 0.5f, 0.5f };
	GLfloat cn[] = { x + 35, y + 70, z + 35};

	basis.setParams(cl, cn, 10, 5, 0, 1);
	basis.drawCylinder(90, 0, 1, 0);
	
}


Arm::~Arm()
{
}
