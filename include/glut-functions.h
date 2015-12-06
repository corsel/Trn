#ifndef GLUT_FUNCTIONS_H_INCLUDED
#define GLUT_FUNCTIONS_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "level.h"

extern Level *activeLevel;

namespace TrnGlutFunctions
{
const int screenWidth = 800;
const int screenHeight = 600;
const bool fullscreen = false;

void init(int *argc, char **argv);
void display(void);
void keyboard(unsigned char argKey, int argX, int argY);
void mouse(int argButton, int argState, int argX, int argY);
}

#endif //GLUT_FUNCTIONS_H_INCLUDED
