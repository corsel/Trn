#include "texture-test.h"

GLuint *textures;
float **buffers;

void loadTexture()
{
	glEnable(GL_TEXTURE_2D);
	glGenTextures(2, textures);
	for (int i = 0; i < 2; i++)
		glBindTexture(GL_TEXTURE_2D, textures[i]);
	createBuffers();	
	glTexImage2D(
		textures[0], 
		0, GL_RGB,
		7, 6,
		0, GL_RGB,
		GL_FLOAT,
		buffers[0]);
	glTexImage2D(
		textures[1], 
		0, GL_RGB,
		5, 3,
		0, GL_RGB,
		GL_FLOAT,
		buffers[1]);
}

void createBuffers()
{
	buffers = new float* [2];
	
	buffers[0] = new float[6*7*3];
	buffers[1] = new float[3*5*3];
	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			buffers[0][i*6+j] = (float)i / 12.0f + (float)j / 14.0f;
			buffers[0][i*6+j+1] = 1.0f - (float)i / 12.0f - (float)j / 14.0f;
			buffers[0][i*6+j+2] = 0.2f;
			
			if (i >= 3 || j >= 5) continue;
			
			buffers[1][i*3+j] = 0.1f;
			buffers[1][i*3+j+1] = 1.0f - (float)i / 20.0f - (float)j / 13.0f;
			buffers[1][i*3+j+2] = 1.0f - (float)i / 20.0f + (float)j / 13.0f;
		}
	}
}
