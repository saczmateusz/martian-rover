#include "Terrain.h"



Terrain::Terrain(unsigned int texID)
{
	glPushMatrix();

	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glBegin(GL_QUADS);
	//glTexCoord2d(1, 1);  glVertex3f(-50, -50, 150);
	//glTexCoord2d(0, 1);  glVertex3f(-50, 50, 150);
	//glTexCoord2d(0, 0);  glVertex3f(50, 50, 150);
	//glTexCoord2d(1, 0);  glVertex3f(50, -50, 150);
	//glEnd();
	


	if (floor.LoadFile("mars.obj"))
	{
		for (int i = 0; i < floor.LoadedMeshes.size(); i++)
		{
			objl::Mesh curMesh = floor.LoadedMeshes[i];

			for (int j = 0; j < curMesh.Indices.size(); j += 3)
			{
				glBegin(GL_TRIANGLES);
				//double random = 0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.55f - 0.5f)));
				//glColor3f(0.55f, 0.22f, 0.07f);
				//if (i == 0) glColor3f(0, 0, 1);
				//glTexCoord2d(curMesh.Vertices[curMesh.Indices[j]].TextureCoordinate.X, curMesh.Vertices[curMesh.Indices[j]].TextureCoordinate.Y); 
				glTexCoord2d(0, 0); 
				glVertex3f(
					curMesh.Vertices[curMesh.Indices[j]].Position.X,
					curMesh.Vertices[curMesh.Indices[j]].Position.Y,
					curMesh.Vertices[curMesh.Indices[j]].Position.Z
				);

				//glTexCoord2d(curMesh.Vertices[curMesh.Indices[j + 1]].TextureCoordinate.X, curMesh.Vertices[curMesh.Indices[j + 1]].TextureCoordinate.Y); 
				glTexCoord2d(0, 1); 
				glVertex3f(
					curMesh.Vertices[curMesh.Indices[j + 1]].Position.X,
					curMesh.Vertices[curMesh.Indices[j + 1]].Position.Y,
					curMesh.Vertices[curMesh.Indices[j + 1]].Position.Z
				);

				//glTexCoord2d(curMesh.Vertices[curMesh.Indices[j + 2]].TextureCoordinate.X, curMesh.Vertices[curMesh.Indices[j + 2]].TextureCoordinate.Y); 
				glTexCoord2d(1, 0); 
				glVertex3f(
					curMesh.Vertices[curMesh.Indices[j + 2]].Position.X,
					curMesh.Vertices[curMesh.Indices[j + 2]].Position.Y,
					curMesh.Vertices[curMesh.Indices[j + 2]].Position.Z
				);
				glEnd();
			}
		}
	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}


Terrain::~Terrain()
{
}
