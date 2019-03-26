#pragma once
#include "../Cylinder/Cylinder.h"
#include "../Parts/Platform/Platform.h"
#include "../Parts/Chassis/Chassis.h"

class Rover
{
public:
	Rover(float x, float y, float z);
	~Rover();

private:
	vector<Cylinder> wheels;
	Chassis chassis;
	Platform platform;
};

