#include "Platform.h"



Platform::Platform(float x, float y, float z)
	: arm(x, y, z)
{
	posX = x;
	posY = y;
	posZ = z;
}


Platform::~Platform()
{
}

void Platform::setTextures(unsigned int texID, unsigned int smokID)
{
	banana = texID;
	arm.setTexture(smokID);
	a[0] = posX + 40;
	a[1] = posY + 40;
	a[2] = posZ + 30;

	b[0] = posX + 75;
	b[1] = posY + 40;
	b[2] = posZ + 30;

	c[0] = posX + 70;
	c[1] = posY + 70;
	c[2] = posZ + 30;

	d[0] = posX + 40;
	d[1] = posY + 90;
	d[2] = posZ + 30;

	color[0] = 0.8f;
	color[1] = 0.3f;
	color[2] = 0.3f;

	LeftFront.setParams(color, a, b, c, d, 5, banana);

	a[0] = posX - 5;
	b[0] = posX + 30;
	c[1] = posY + 90;
	c[0] = posX + 30;
	d[1] = posY + 70;
	d[0] = posX;
	RightFront.setParams(color, a, b, c, d, 5, banana);

	a[1] = posY - 20;
	a[0] = posX - 13;
	b[1] = posY;
	b[0] = posX + 30;
	c[1] = posY + 35;
	c[0] = posX + 30;
	d[1] = posY + 35;
	d[0] = posX - 5.5f;
	RightBack.setParams(color, a, b, c, d, 5, banana);

	a[0] = posX + 83;
	b[0] = posX + 40;
	c[0] = posX + 40;
	d[0] = posX + 75.5f;
	LeftBack.setParams(color, a, b, c, d, 5, banana);

	GLfloat cl[] = { 0.5f, 0.5f, 0.5f };
	GLfloat cn[] = { posX + 35, posY + 40, posZ + 41 };

	engine.setParams(cl, cn, 15, 30);

	cn[1] = posY + 10;

	engineCore.setParams(cl, cn, 15, 25, 0, 1);

	cl[0] = 1;
	cl[1] = 0.4f;
	cl[2] = 0.3f;

	cn[1] = posY - 55;

	thrust.setParams(cl, cn, 10, 40);
}


void Platform::drawPlatform(GLfloat rot, GLfloat xdg, GLfloat ydg, GLfloat zdg)
{
	LeftFront.drawCuboid(0, 0, 0, 0);
	RightFront.drawCuboid(0, 0, 0, 0);
	RightBack.drawCuboid(0, 0, 0, 0);
	LeftBack.drawCuboid(0, 0, 0, 0);

	glPushMatrix();

	glTranslatef(engine.center[0], (engine.center[2]-20), engine.center[2]); // powrot do pozycji wyjsciowej
	glRotatef(rot, xdg, ydg, zdg); // obrot wokol punktu 0,0 po osi Z
	glTranslatef(-engine.center[0], -(engine.center[2]-20), -engine.center[2]);

	engine.drawCone(-90, 1, 0, 0);
	engineCore.drawCylinder(-90, 0, 0, 1);
	thrust.drawCone(90, 1, 0, 0);
	glPopMatrix();

	arm.drawArm();
}
