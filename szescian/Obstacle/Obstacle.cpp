#include "Obstacle.h"



Obstacle::Obstacle(float xx, float yy, float zz, float scale)
{
	this->scale = scale;
	posX = xx;
	posY = yy;
	posZ = zz;
}


Obstacle::~Obstacle()
{
}

void Obstacle::setTexture(unsigned int texID)
{
	texture = texID;
}

void Obstacle::drawObstacle()
{
	glPushMatrix();

	glRotatef(0, 0, 0, 0);
	glScalef(scale, scale, scale);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1.0f, 1.0f, 1.0f);

	if (floor.LoadFile("malphite.obj"))
	{
		for (int i = 0; i < floor.LoadedMeshes.size(); i++)
		{
			objl::Mesh curMesh = floor.LoadedMeshes[i];

			for (int j = 0; j < curMesh.Indices.size(); j += 3)
			{
				glBegin(GL_TRIANGLES);
				//double random = 0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.55f - 0.5f)));
				glColor3f(0.5f, 0.5f, 0.5f);
				//if (i == 0) glColor3f(0, 0, 1);
				glTexCoord2d(0, 0); glVertex3f(
					posX + curMesh.Vertices[curMesh.Indices[j]].Position.X,
					posY + curMesh.Vertices[curMesh.Indices[j]].Position.Y,
					posZ + curMesh.Vertices[curMesh.Indices[j]].Position.Z
				);

				glTexCoord2d(0, 1); glVertex3f(
					posX + curMesh.Vertices[curMesh.Indices[j + 1]].Position.X,
					posY + curMesh.Vertices[curMesh.Indices[j + 1]].Position.Y,
					posZ + curMesh.Vertices[curMesh.Indices[j + 1]].Position.Z
				);

				glTexCoord2d(1, 1); glVertex3f(
					posX + curMesh.Vertices[curMesh.Indices[j + 2]].Position.X,
					posY + curMesh.Vertices[curMesh.Indices[j + 2]].Position.Y,
					posZ + curMesh.Vertices[curMesh.Indices[j + 2]].Position.Z
				);
				glEnd();
				BB[0] = max4(curMesh.Vertices[curMesh.Indices[j]].Position.X, curMesh.Vertices[curMesh.Indices[j + 1]].Position.X, curMesh.Vertices[curMesh.Indices[j + 2]].Position.X, BB[0]);
				BB[1] = max4(curMesh.Vertices[curMesh.Indices[j]].Position.Y, curMesh.Vertices[curMesh.Indices[j + 1]].Position.Y, curMesh.Vertices[curMesh.Indices[j + 2]].Position.Y, BB[1]);
				BB[2] = min4(curMesh.Vertices[curMesh.Indices[j]].Position.X, curMesh.Vertices[curMesh.Indices[j + 1]].Position.X, curMesh.Vertices[curMesh.Indices[j + 2]].Position.X, BB[2]);
				BB[3] = min4(curMesh.Vertices[curMesh.Indices[j]].Position.Y, curMesh.Vertices[curMesh.Indices[j + 1]].Position.Y, curMesh.Vertices[curMesh.Indices[j + 2]].Position.Y, BB[3]);
			}
		}
	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}


GLfloat Obstacle::max4(GLfloat a, GLfloat b, GLfloat c, GLfloat d)
{
	return std::max(a, std::max(b, std::max(c, d)));
}


GLfloat Obstacle::min4(GLfloat a, GLfloat b, GLfloat c, GLfloat d)
{
	return std::min(a, std::min(b, std::min(c, d)));
}


GLfloat * Obstacle::getBB()
{
	return BB;
}