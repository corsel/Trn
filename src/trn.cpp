#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include "glut-functions.h"
#include "xml-parser.h"
#include "animation.h"

int main(int argc, char **argv)
{
/*
	TrnGlutFunctions::init(&argc, argv);
	activeLevel = new Level();
	glutMainLoop();
	parseXml("data/test-file");
*/
	Vec2 testRef(0.0f, 0.0f);
	Animation<Vec2> *test = new Vec2Lerp(&testRef, Vec2(1.0f, 0.0f), Vec2(2.0f, 1.0f), 5.0f);
	while(test->getIsAlive())
	{
		test->step(0.1f);
	}
	std::cout << "\nfin.\n";
	return 0;
}
