#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <GL/freeglut.h>

const int numTextures = 3;
const int bitmapHeaderOffset = 123;

class TextureServer //Singleton
{
private:
	static TextureServer *instance;
	GLuint *textureHandle;
	char **textureBuffer;
	int *textureSize;
		
	TextureServer(void);
	
public:
	~TextureServer(void);
	static TextureServer *getInstance(void);
	void generateTexture(const char *argFileName, GLuint argTextureIndex, const int argWidth, const int argHeight);
	void bindTexture(GLuint argTextureIndex);
};

#endif //TEXTURE_H_INCLUDED
