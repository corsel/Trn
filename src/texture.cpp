#include <iostream>
#include "texture.h"

TextureServer *TextureServer::instance = NULL;
GLuint *TextureServer::textureHandle = NULL;
TextureServer::TextureServer() 
{
	TextureServer::textureHandle = new GLuint[numTextures];
	glGenTextures(numTextures, TextureServer::textureHandle);
	
	//debug
	for (int i = 0; i < 3; i++)
	{
		std::cout << "Debug - TextureServer::TextureServer: " << TextureServer::textureHandle[i] << std::endl;
	}
}
TextureServer::~TextureServer()
{
	delete [] TextureServer::textureHandle;
}
TextureServer *TextureServer::getInstance() //static
{
	if (instance == NULL)
		instance = new TextureServer();
	return instance;
}
void TextureServer::bindTexture(GLuint argTextureIndex) //static
{
	if (argTextureIndex >= numTextures)
	{
		std::cout << "Error - TextureServer::bindTexture: Invalid texture index: " << argTextureIndex << std::endl;
	}
	glBindTexture(GL_TEXTURE_2D, TextureServer::textureHandle[argTextureIndex]);
}
