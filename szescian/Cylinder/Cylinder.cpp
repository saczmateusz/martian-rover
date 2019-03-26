#include "Cylinder.h"



Cylinder::Cylinder(GLfloat * colour, GLfloat * cen, GLfloat r, GLfloat hh, GLfloat grad, int s)
{
	setParams(colour, cen, r, hh, grad, s);
}


Cylinder::Cylinder()
{
}


Cylinder::~Cylinder()
{
}

void Cylinder::setParams(GLfloat * colour, GLfloat * cen, GLfloat r, GLfloat hh, GLfloat grad, int s)
{
	color[0] = colour[0];
	color[1] = colour[1];
	color[2] = colour[2];

	center[0] = cen[0];
	center[1] = cen[1];
	center[2] = cen[2];

	radius = r;
	height = hh;
	gradient = grad;
	side = s;
}

void Cylinder::drawCylinder()
{
	GLfloat x = center[0], y = center[1], z = center[2];
	angle = 0;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(x, y, z);
	do
	{
		x = GLfloat(center[0] + radius * sin(angle));
		y = GLfloat(center[1] + radius * cos(angle));

		glVertex3f(x, y, z);

		angle += GLfloat(GL_PI / 10);
	} while (angle <= 2 * (GL_PI + 0.1));
	glEnd();


	x = center[0];
	y = center[1];
	angle = 0;
	glBegin(GL_TRIANGLE_STRIP);
	glColor3fv(color);
	do
	{
		z = center[2];
		x = GLfloat(center[0] + radius * sin(angle));
		y = GLfloat(center[1] + radius * cos(angle));

		glVertex3f(x, y, z);

		z += height * side;
		x += gradient;
		glVertex3f(x, y, z);

		angle += GLfloat(GL_PI / 10);
	} while (angle <= 2 * (GL_PI + 0.1));
	glEnd();

	x = center[0];
	y = center[1];
	z = (center[2] + height * side);
	angle = 0;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(x + gradient, y, z);
	do
	{
		x = gradient + GLfloat(center[0] + radius * sin(angle));
		y = GLfloat(center[1] + radius * cos(angle));

		glVertex3f(x, y, z);


		angle += GLfloat(GL_PI / 10);
	} while (angle <= 2 * (GL_PI + 0.1));
	glEnd();

}
