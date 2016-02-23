#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <GL/freeglut.h>

const int numTextures = 3;

class TextureServer //Singleton
{
private:
	static TextureServer *instance;
	GLuint *textureHandle;
		
	TextureServer(void);
	
public:
	~TextureServer(void);
	static TextureServer *getInstance(void);
};

#endif //TEXTURE_H_INCLUDED
