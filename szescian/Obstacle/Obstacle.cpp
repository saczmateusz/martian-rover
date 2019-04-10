#include "Obstacle.h"



Obstacle::Obstacle(float xx, float yy, float zz, float scale)
{
	glPushMatrix();

	glRotatef(0, 0, 0, 0);
	glScalef(scale , scale, scale);

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
				glVertex3f(
					xx + curMesh.Vertices[curMesh.Indices[j]].Position.X,
					yy + curMesh.Vertices[curMesh.Indices[j]].Position.Y,
					zz + curMesh.Vertices[curMesh.Indices[j]].Position.Z
				);

				glVertex3f(
					xx + curMesh.Vertices[curMesh.Indices[j + 1]].Position.X,
					yy + curMesh.Vertices[curMesh.Indices[j + 1]].Position.Y,
					zz + curMesh.Vertices[curMesh.Indices[j + 1]].Position.Z
				);

				glVertex3f(
					xx + curMesh.Vertices[curMesh.Indices[j + 2]].Position.X,
					yy + curMesh.Vertices[curMesh.Indices[j + 2]].Position.Y,
					zz + curMesh.Vertices[curMesh.Indices[j + 2]].Position.Z
				);
				glEnd();
			}
		}
	}

	glPopMatrix();
}


Obstacle::~Obstacle()
{
}
