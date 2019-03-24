#pragma once
#include "Grid.h"
#include "Wheel.h"

class Rover
{
public:
	Rover(float x, float y, float z);
	~Rover();

private:
	Grid grid;
	Wheel kolo1;
	Wheel kolo2;
	Wheel kolo3;
	Wheel kolo4;
	Wheel kolo5;
	Wheel kolo6;
};

