#include <iostream>
#include <GL/freeglut.h>
#include "glut-functions.h"
#include "xml-parser.h"

int main(int argc, char **argv)
{
/*
	TrnGlutFunctions::init(&argc, argv);
	activeLevel = new Level();
	glutMainLoop();
*/
	parseXml("data/test-file");
	std::cout << "\nfin.\n";
	return 0;
}
