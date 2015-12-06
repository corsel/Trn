#ifndef TEXTURE_TEST_H_INCLUDED
#define TEXTURE_TEST_H_INCLUDED

#include "GL/gl.h"
#include "GL/freeglut.h"

extern GLuint *textures;
extern float **buffers;

void loadTexture(void);
void createBuffers(void);

#endif //TEXTURE_TEST_H_INCLUDED

