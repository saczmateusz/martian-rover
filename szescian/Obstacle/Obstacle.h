#pragma once
#define NOMINMAX
#include "../../DEFINITIONS.h"
#include "../../OBJ_Loader.h"

class Obstacle
{
public:
	Obstacle(float xx, float yy, float zz, float scale);
	~Obstacle();
	void setTexture(unsigned int texID);
	void drawObstacle();
	GLfloat max4(GLfloat a, GLfloat b, GLfloat c, GLfloat d);
	GLfloat min4(GLfloat a, GLfloat b, GLfloat c, GLfloat d);
	GLfloat *getBB();

public:
	objl::Loader floor;
	float posX;
	float posY;
	float posZ;
	unsigned int texture;
	float scale;
	GLfloat BB[4] = { 0,0,0,0 };// X,Y,x,y
};

