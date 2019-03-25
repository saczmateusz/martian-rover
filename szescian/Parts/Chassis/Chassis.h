#pragma once
#include "../../definitions.h"
#include "Frame/Frame.h"
#include "Axle/Axle.h"

class Chassis
{
public:
	Chassis(float x, float y, float z);
	~Chassis();

private:
	Frame frame;
	Axle axle1;
	Axle axle2;
	Axle axle3;
	Axle axle4;
	Axle axle5;
	Axle axle6;
};

