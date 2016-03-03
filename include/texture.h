#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <GL/freeglut.h>

const int numTextures = 3;

class TextureServer //Singleton
{
private:
	static TextureServer *instance;
	GLuint *textureHandle;
	char **textureBuffer;
		
	TextureServer(void);
	
public:
	~TextureServer(void);
	static TextureServer *getInstance(void);
	void generateTexture(const char *argFileName, GLuint argTextureIndex);
	void bindTexture(GLuint argTextureIndex);
};

#endif //TEXTURE_H_INCLUDED
