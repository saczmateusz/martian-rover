#pragma once
#include "../../definitions.h"
#include "../../Cylinder/Cylinder.h"
#include "Frame/Frame.h"

class Chassis
{
public:
	Chassis(float x, float y, float z);
	~Chassis();
	void setFrameX(float a);
	void setFrameY(float a);
	void setFrameZ(float a);
	float getFrameX();
	float getFrameY();
	float getFrameZ();

private:
	Frame frame;
	vector<Cylinder> axles;
	float frameX;
	float frameY;
	float frameZ;
};

