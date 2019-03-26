#include "Cuboid.h"



Cuboid::Cuboid(GLfloat * colour, GLfloat * aa, GLfloat * bb, GLfloat * cc, GLfloat * dd, GLfloat hh)
{
	setParams(colour, aa, bb, cc, dd, hh);
}

Cuboid::Cuboid()
{
}


Cuboid::~Cuboid()
{
}

void Cuboid::drawCuboid()
{
	GLfloat e[3] = { a[0] + height, a[1], a[2] };
	GLfloat f[3] = { b[0] + height, b[1], b[2] };
	GLfloat g[3] = { c[0] + height, c[1], c[2] };
	GLfloat j[3] = { d[0] + height, d[1], d[2] };

	glColor3fv(color);
	glBegin(GL_POLYGON);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3fv(e);
	glVertex3fv(f);
	glVertex3fv(g);
	glVertex3fv(j);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(e);
	glVertex3fv(f);
	glVertex3fv(b);
	glVertex3fv(a);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(d);
	glVertex3fv(j);
	glVertex3fv(g);
	glVertex3fv(c);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(b);
	glVertex3fv(f);
	glVertex3fv(g);
	glVertex3fv(c);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(j);
	glVertex3fv(d);
	glVertex3fv(a);
	glVertex3fv(e);
	glEnd();
}

void Cuboid::setParams(GLfloat * colour, GLfloat * aa, GLfloat * bb, GLfloat * cc, GLfloat * dd, GLfloat hh)
{
	a[0] = aa[0];
	a[1] = aa[1];
	a[2] = aa[2];

	b[0] = bb[0];
	b[1] = bb[1];
	b[2] = bb[2];

	c[0] = cc[0];
	c[1] = cc[1];
	c[2] = cc[2];

	d[0] = dd[0];
	d[1] = dd[1];
	d[2] = dd[2];

	color[0] = colour[0];
	color[1] = colour[1];
	color[2] = colour[2];

	height = hh;
}