#include "Frame.h"



Frame::Frame(float x, float y, float z)
{
	x += 20;
	z += 25;
	glBegin(GL_POLYGON);
	glColor3f(0.8f, 0.3f, 0.3f);
	glVertex3f(x, y, z);
	y += 80;
	glVertex3f(x, y, z);
	x += 10;
	glVertex3f(x, y, z);
	y -= 80;
	glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.8f, 0.3f, 0.3f);
	glVertex3f(x, y, z);
	y += 80;
	glVertex3f(x, y, z);
	z += 20;
	glVertex3f(x, y, z);
	y -= 80;
	glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.8f, 0.3f, 0.3f);
	glVertex3f(x, y, z);
	y += 80;
	glVertex3f(x, y, z);
	x -= 10;
	glVertex3f(x, y, z);
	y -= 80;
	glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.8f, 0.3f, 0.3f);
	glVertex3f(x, y, z);
	y += 80;
	glVertex3f(x, y, z);
	z -= 20;
	glVertex3f(x, y, z);
	y -= 80;
	glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.8f, 0.3f, 0.3f);
	glVertex3f(x, y, z);
	z += 20;
	glVertex3f(x, y, z);
	x += 10;
	glVertex3f(x, y, z);
	z -= 20;
	glVertex3f(x, y, z);
	glEnd();

	y += 80;
	glBegin(GL_POLYGON);
	glColor3f(0.8f, 0.3f, 0.3f);
	glVertex3f(x, y, z);
	z += 20;
	glVertex3f(x, y, z);
	x -= 10;
	glVertex3f(x, y, z);
	z -= 20;
	glVertex3f(x, y, z);
	glEnd();
}


Frame::~Frame()
{
}
