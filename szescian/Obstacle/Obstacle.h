#pragma once
#include "../definitions.h"
#include "../Cone/Cone.h";
#include "../Cylinder/Cylinder.h";

class Obstacle
{
public:
	Obstacle();
	~Obstacle();

public:
	vector<Cylinder> basis;
	Cylinder core;
	Cone apex;

};

