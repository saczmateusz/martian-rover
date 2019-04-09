#pragma once
#include "../../../DEFINITIONS.h"
#include "../../Cylinder/Cylinder.h"
#include "Frame/Frame.h"

class Chassis
{
public:
	Chassis(float x, float y, float z);
	~Chassis();

private:
	Frame frame;
	vector<Cylinder> axles;
};

