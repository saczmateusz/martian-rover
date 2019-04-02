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

void Cylinder::drawCylinder(GLfloat rot, GLfloat xdg, GLfloat ydg, GLfloat zdg)
{
	glPushMatrix();

	if (rot)
	{
		glTranslatef(center[0], center[1], center[2]);
		glRotatef(rot, xdg, ydg, zdg);
		glTranslatef(-center[0], -center[1], -center[2]);
	}

	GLfloat x = center[0], y = center[1], z = center[2];
	angle = 0;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(x, y, z);
	do
	{
		y = GLfloat(center[1] + radius * cos(angle));
		z = GLfloat(center[2] + radius * sin(angle));

		glVertex3f(x, y, z);

		angle += GLfloat(GL_PI / PRECISION);
	} while (angle <= 2 * (GL_PI + 0.1));
	glEnd();


	y = center[1];
	z = center[2];
	angle = 0;
	glBegin(GL_TRIANGLE_STRIP);
	glColor3fv(color);
	do
	{
		x = center[0];
		y = GLfloat(center[1] + radius * cos(angle));
		z = GLfloat(center[2] + radius * sin(angle));

		glVertex3f(x, y, z);

		x += height * side;
		z += gradient;
		glVertex3f(x, y, z);

		angle += GLfloat(GL_PI / PRECISION);
	} while (angle <= 2 * (GL_PI + 0.1));
	glEnd();

	x = center[0] + height * side;
	y = center[1];
	z = center[2];
	angle = 0;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(x, y, z + gradient);
	do
	{
		y = GLfloat(center[1] + radius * cos(angle));
		z = gradient + GLfloat(center[2] + radius * sin(angle));

		glVertex3f(x, y, z);


		angle += GLfloat(GL_PI / PRECISION);
	} while (angle <= 2 * (GL_PI + 0.1));
	glEnd();
	glPopMatrix();
}
