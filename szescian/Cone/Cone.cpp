#include "Cone.h"



Cone::Cone(GLfloat * colour, GLfloat * cen, GLfloat r, GLfloat hh)
{
	setParams(colour, cen, r, hh);
}

Cone::Cone()
{
}

Cone::~Cone()
{
}

void Cone::setParams(GLfloat * colour, GLfloat * cen, GLfloat r, GLfloat hh)
{
	color[0] = colour[0];
	color[1] = colour[1];
	color[2] = colour[2];

	center[0] = cen[0];
	center[1] = cen[1];
	center[2] = cen[2];

	radius = r;
	height = hh;
}

void Cone::drawCone(GLfloat rot, GLfloat xdg, GLfloat ydg, GLfloat zdg)
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
	glColor3fv(color);
	glVertex3f(x, y, z);
	z -= height;
	do
	{
		x = GLfloat(center[0] + radius * cos(angle));
		y = GLfloat(center[1] + radius * sin(angle));

		glVertex3f(x, y, z);
		angle += GLfloat(GL_PI / PRECISION);
	} while (angle <= 2 * (GL_PI + 0.1));
	glEnd();

	glPopMatrix();
}
