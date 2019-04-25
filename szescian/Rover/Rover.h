#pragma once
#include "../Cylinder/Cylinder.h"
#include "../Parts/Platform/Platform.h"
#include "../Parts/Chassis/Chassis.h"

class Rover
{
public:
	Rover(float x, float y, float z);
	~Rover();
	void setBackFrameX(float a);
	void setBackFrameY(float a);
	void setBackFrameZ(float a);
	float getBackFrameX();
	float getBackFrameY();
	float getBackFrameZ();


private:
	vector<Cylinder> wheels;
	Chassis chassis;
	Platform platform;
	float backFrameX;
	float backFrameY;
	float backFrameZ;
};

