#include "Rover.h"



Rover::Rover(float x, float y, float z) :
	grid(1000),
	kolo1(x, y + 0,  z + 0,  10),
	kolo2(x, y + 30, z + 0,  10),
	kolo3(x, y + 60, z + 0,  10),
	kolo4(x, y + 0,  z + 50, 10),
	kolo5(x, y + 30, z + 50, 10),
	kolo6(x, y + 60, z + 50, 10)
{
	
}


Rover::~Rover()
{
}
