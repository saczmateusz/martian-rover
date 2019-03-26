#pragma once
#include "../../Cylinder/Cylinder.h"

class Arm
{
public:
	Arm(float x, float y, float z);
	~Arm();
	Cylinder basis;
};

