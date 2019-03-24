#pragma once
#include "../Grid/Grid.h"
#include "../Parts/Wheel/Wheel.h"
#include "../Parts/Platform/Platform.h"
#include "../Parts/Chassis/Chassis.h"
#include "../Parts/Arm/Arm.h"

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

