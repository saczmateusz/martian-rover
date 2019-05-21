#pragma once
#include "../Cylinder/Cylinder.h"
#include "../Parts/Platform/Platform.h"
#include "../Parts/Chassis/Chassis.h"
#include <vector>

class Rover
{
public:
	Rover(float x, float y, float z);
	~Rover();
	void drawRover(GLfloat rot, GLfloat xdg, GLfloat ydg, GLfloat zdg);
	void setTextures(unsigned int texID, unsigned int smokID);
	vector<float> getPos();

public:
	vector<Cylinder> wheels;
	Chassis chassis;
	Platform platform;
	float posX;
	float posY;
	float posZ;
	
};

