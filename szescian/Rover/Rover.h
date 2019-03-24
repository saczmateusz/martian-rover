#pragma once
#include "../Grid/Grid.h"
#include "../Parts/Wheel/Wheel.h"
#include "../Parts/Platform/Platform.h"
#include "../Parts/Chassis/Chassis.h"
#include "../Parts/Chassis/Frame/Frame.h"
#include "../Parts/Chassis/Axle/Axle.h"
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
	Frame frame;
	Axle axle1;
	Axle axle2;
	Axle axle3;
	Axle axle4;
	Axle axle5;
	Axle axle6;

};

