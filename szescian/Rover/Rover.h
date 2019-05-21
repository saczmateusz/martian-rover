#pragma once
#include "../Cylinder/Cylinder.h"
#include "../Parts/Platform/Platform.h"
#include "../Parts/Chassis/Chassis.h"

class Rover
{
public:
	Rover(float x, float y, float z);
	~Rover();
	void drawRover();
	void setTextures(unsigned int texID, unsigned int smokID);

public:
	vector<Cylinder> wheels;
	Chassis chassis;
	Platform platform;
	float posX;
	float posY;
	float posZ;
	
};

