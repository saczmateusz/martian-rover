#include "Axle.h"



Axle::Axle(float xs, float ys, float zs, char side)
{
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.3f, 0.3f, 0.8f);
	do
	{
		z = zs;
		x = GLfloat(xs + r * sin(angle));
		y = GLfloat(ys + r * cos(angle));

		glVertex3f(x, y, z);

		z -= 23 * side;
		x += 15;
		glVertex3f(x, y, z);

		angle += GLfloat(GL_PI / 10);
	} while (angle <= 2 * (GL_PI + 0.1));
	glEnd();
}


Axle::~Axle()
{
}
