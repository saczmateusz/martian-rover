#include "Cuboid.h"



Cuboid::Cuboid(GLfloat * colour, GLfloat * aa, GLfloat * bb, GLfloat * cc, GLfloat * dd, GLfloat hh, unsigned int texID)
{
	setParams(colour, aa, bb, cc, dd, hh, texID);
}

Cuboid::Cuboid()
{
}


Cuboid::~Cuboid()
{
}

void Cuboid::drawCuboid(GLfloat rot, GLfloat xdg, GLfloat ydg, GLfloat zdg)
{
	glPushMatrix();

	if (rot)
	{
		glTranslatef(c[0], c[1], c[2]);
		glRotatef(rot, xdg, ydg, zdg);
		glTranslatef(-c[0], -c[1], -c[2]);
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	GLfloat e[3] = { a[0], a[1], a[2] + height };
	GLfloat f[3] = { b[0], b[1], b[2] + height };
	GLfloat g[3] = { c[0], c[1], c[2] + height };
	GLfloat j[3] = { d[0], d[1], d[2] + height };
	if(tex == 0)
		glColor3fv(color);
	else
		glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3fv(a);
	glTexCoord2d(0, 1); glVertex3fv(b);
	glTexCoord2d(1, 1); glVertex3fv(c);
	glTexCoord2d(1, 0); glVertex3fv(d);
	glEnd();


	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3fv(a);
	glTexCoord2d(0, 1); glVertex3fv(b);
	glTexCoord2d(1, 1); glVertex3fv(f);
	glTexCoord2d(1, 0); glVertex3fv(e);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3fv(a);
	glTexCoord2d(0, 1); glVertex3fv(d);
	glTexCoord2d(1, 1); glVertex3fv(j);
	glTexCoord2d(1, 0); glVertex3fv(e);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3fv(f);
	glTexCoord2d(0, 1); glVertex3fv(g);
	glTexCoord2d(1, 1); glVertex3fv(j);
	glTexCoord2d(1, 0); glVertex3fv(e);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3fv(f);
	glTexCoord2d(0, 1); glVertex3fv(g);
	glTexCoord2d(1, 1); glVertex3fv(c);
	glTexCoord2d(1, 0); glVertex3fv(b);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3fv(j);
	glTexCoord2d(0, 1); glVertex3fv(g);
	glTexCoord2d(1, 1); glVertex3fv(c);
	glTexCoord2d(1, 0); glVertex3fv(d);
	glEnd();


	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void Cuboid::setParams(GLfloat * colour, GLfloat * aa, GLfloat * bb, GLfloat * cc, GLfloat * dd, GLfloat hh, unsigned int texID)
{
	tex = texID;

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