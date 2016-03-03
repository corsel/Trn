#include "texture.h"

TextureServer *TextureServer::instance = NULL;
TextureServer::TextureServer() 
{
	TextureServer::textureHandle = new GLuint[numTextures];
	glGenTextures(numTextures, TextureServer::textureHandle);
	
	textureBuffer = new char*[numTextures];
	textureSize = new int[numTextures * 2];
}
TextureServer::~TextureServer()
{
	delete [] TextureServer::textureHandle;
	delete [] textureBuffer;
	delete [] textureSize;
}
TextureServer *TextureServer::getInstance() //static
{
	if (instance == NULL)
		instance = new TextureServer();
	return instance;
}
void TextureServer::generateTexture(const char *argFileName, GLuint argTextureIndex, const int argWidth, const int argHeight)
{
	if (argTextureIndex >= numTextures)
	{
		std::cout << "Error - TextureServer::generateTexture: Invalid texture index: " << argTextureIndex << std::endl;
		return;
	}
	std::ifstream bitmapFile;
	bitmapFile.open(argFileName);
	if (!bitmapFile.is_open())
	{
		std::cout << "Error - TextureServer::generateTexture: Invalid texture file: " << argFileName << std::endl;
		return;
	}
	std::cout << "Debug - TextureServer::generateTexture: Texture " << argTextureIndex << " load successful.\n"; //Debug
	textureSize[argTextureIndex * 2] = argWidth;
	textureSize[argTextureIndex * 2 + 1] = argHeight;
	int bufferSize;
	bitmapFile.seekg(0, std::ios_base::end);
	bufferSize = bitmapFile.tellg();
	bitmapFile.seekg(0, std::ios_base::beg);
	std::cout << "Debug - TextureServer::generateTexture: Texture size: " << bufferSize << std::endl; //Debug
	textureBuffer[argTextureIndex] = new char [bufferSize];
	bitmapFile.read(textureBuffer[argTextureIndex], bufferSize * sizeof(char));
	
	//Debug
	std::cout << "Debug - TextureServer::generateTexture: Behold! Incoming bitmap stream: \n";
	for (int i = 0; i < bufferSize; i++)
	{
		if (i % 40 == 0)
			std::cout << std::endl;
		std::cout << /*(short int)*/textureBuffer[0][i] << " ";
	}
	//
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize[argTextureIndex * 2], textureSize[argTextureIndex * 2 + 1], 0, GL_BGR, GL_UNSIGNED_BYTE/*??*/, (GLvoid*)(textureBuffer[argTextureIndex] + bitmapHeaderOffset));
	
	bitmapFile.close();
}
void TextureServer::bindTexture(GLuint argTextureIndex)
{
	if (argTextureIndex >= numTextures)
	{
		std::cout << "Error - TextureServer::bindTexture: Invalid texture index: " << argTextureIndex << std::endl;
		return;
	}
	glBindTexture(GL_TEXTURE_2D, TextureServer::textureHandle[argTextureIndex]);
}
