#include "Rover.h"



Rover::Rover(float x, float y, float z) :
	grid(1000),
	kolo1(x, y + 0,  z + 0,  10),
	kolo2(x, y + 30, z + 0,  10),
	kolo3(x, y + 60, z + 0,  10),
	kolo4(x, y + 0,  z + 60, 10),
	kolo5(x, y + 30, z + 60, 10),
	kolo6(x, y + 60, z + 60, 10),
	frame(x, y, z),
	axle1(x + 10, y + 10, z + 63, 1),
	axle2(x + 10, y + 40, z + 63, 1),
	axle3(x + 10, y + 70, z + 63, 1),
	axle4(x + 10, y + 10, z + 7, -1),
	axle5(x + 10, y + 40, z + 7, -1),
	axle6(x + 10, y + 70, z + 7, -1)
{
	
}


Rover::~Rover()
{
}
