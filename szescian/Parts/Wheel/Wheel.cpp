#include "Wheel.h"



Wheel::Wheel(float xs, float ys, float zs, float r)
{
	xs += r;
	ys += r;
	GLfloat angle = 0;
	GLfloat x, y, z;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(xs, ys, zs + 3);
	z = zs;
	do
	{
		x = GLfloat(xs + r * sin(angle));
		y = GLfloat(ys + r * cos(angle));

		glVertex3f(x, y, z);


		angle += GLfloat(GL_PI / 10);
	} while (angle <= 2 * (GL_PI + 0.1));
	glEnd();


	zs += 12;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(xs, ys, zs - 3);
	angle = 0;
	z = zs;
	do
	{
		x = GLfloat(xs + r * sin(angle));
		y = GLfloat(ys + r * cos(angle));

		glVertex3f(x, y, z);


		angle += GLfloat(GL_PI / 10);
	} while (angle <= 2 * (GL_PI + 0.1));
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.3f, 0.3f, 0.3f);
	angle = 0;
	do
	{
		z = zs;
		x = GLfloat(xs + r * sin(angle));
		y = GLfloat(ys + r * cos(angle));

		glVertex3f(x, y, z);

		z -= 12;
		glVertex3f(x, y, z);

		angle += GLfloat(GL_PI / 10);
	} while (angle <= 2 * (GL_PI + 0.1));
	glEnd();
}


Wheel::~Wheel()
{
}
