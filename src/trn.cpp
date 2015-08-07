#include <iostream>
#include <GL/freeglut.h>
#include "glut-functions.h"

int main(int argc, char **argv)
{
	TrnGlutFunctions::init(&argc, argv);
	activeLevel = new Level();
	glutMainLoop();
	return 0;
}
