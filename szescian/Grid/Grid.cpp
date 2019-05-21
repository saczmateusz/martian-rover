#include "Grid.h"



Grid::Grid(int size)
{
	this->size = size;
}


Grid::~Grid()
{
}

void Grid::drawGrid()
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f((float)size, 1, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, (float)size, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, (float)size);
	glColor3f(1, 1, 1);
	glEnd();
}