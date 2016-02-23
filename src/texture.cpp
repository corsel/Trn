#include <iostream>
#include "texture.h"

TextureServer *TextureServer::instance = NULL;
TextureServer::TextureServer() 
{
	textureHandle = new GLuint[numTextures];
	glGenTextures(numTextures, textureHandle);
	
	//debug
	for (int i = 0; i < 3; i++)
	{
		std::cout << "Debug - TextureServer::TextureServer: " << textureHandle[i] << std::endl;
	}
}
TextureServer::~TextureServer()
{
	delete [] textureHandle;
}
TextureServer *TextureServer::getInstance()
{
	if (instance == NULL)
		instance = new TextureServer();
	return instance;
}
