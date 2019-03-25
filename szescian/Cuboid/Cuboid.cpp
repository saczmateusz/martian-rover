#include "Cuboid.h"



Cuboid::Cuboid(GLfloat * a, GLfloat * b, GLfloat * c, GLfloat * d, GLfloat h)
{
	drawCuboid(a, b, c, d, h);
}

Cuboid::Cuboid()
{
}


Cuboid::~Cuboid()
{
}

void Cuboid::drawCuboid(GLfloat * a, GLfloat * b, GLfloat * c, GLfloat * d, GLfloat h)
{
	GLfloat e[3] = { a[0] + h, a[1], a[2] };
	GLfloat f[3] = { b[0] + h, b[1], b[2] };
	GLfloat g[3] = { c[0] + h, c[1], c[2] };
	GLfloat j[3] = { d[0] + h, d[1], d[2] };

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();


	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3fv(e);
	glVertex3fv(f);
	glVertex3fv(g);
	glVertex3fv(j);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3fv(e);
	glVertex3fv(f);
	glVertex3fv(b);
	glVertex3fv(a);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3fv(d);
	glVertex3fv(j);
	glVertex3fv(g);
	glVertex3fv(c);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3fv(b);
	glVertex3fv(f);
	glVertex3fv(g);
	glVertex3fv(c);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3fv(j);
	glVertex3fv(d);
	glVertex3fv(a);
	glVertex3fv(e);
	glEnd();
}
