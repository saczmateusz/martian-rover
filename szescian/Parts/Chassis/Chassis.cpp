#include "Chassis.h"



Chassis::Chassis(float x, float y, float z) :
	frame(x, y, z),
	axle1(x + 10, y + 10, z + 63, 1),
	axle2(x + 10, y + 40, z + 63, 1),
	axle3(x + 10, y + 70, z + 63, 1),
	axle4(x + 10, y + 10, z + 7, -1),
	axle5(x + 10, y + 40, z + 7, -1),
	axle6(x + 10, y + 70, z + 7, -1)
{
}


Chassis::~Chassis()
{
}
