#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <GL/freeglut.h>

const int numTextures = 3;

class TextureServer //Singleton
{
private:
	static TextureServer *instance;
	static GLuint *textureHandle;
		
	TextureServer(void);
	
public:
	~TextureServer(void);
	static TextureServer *getInstance(void);
	static void bindTexture(GLuint argTextureIndex);
};

#endif //TEXTURE_H_INCLUDED
