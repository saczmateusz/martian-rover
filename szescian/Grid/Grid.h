#pragma once
#include "../../DEFINITIONS.h"

class Grid
{
public:
	Grid(int size);
	~Grid();

private:
	void DrawGrid(int HALF_GRID_SIZE);
};

