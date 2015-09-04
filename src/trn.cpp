#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include "glut-functions.h"
#include "xml-parser.h"
#include "animation.h"

namespace Test
{

void displayTest(int argc, char **argv)
{
	TrnGlutFunctions::init(&argc, argv);
	activeLevel = new Level();
	glutMainLoop();
	parseXml("data/test-file");
}

void animationTest()
{
	Vec2 testRef(0.0f, 0.0f);
	Vec2 testRef2(0.0f, 0.0f);
	Animation *testAnim = new Vec2Lerp(&testRef, Vec2(1.0f, 0.0f), Vec2(2.0f, 1.0f), 5000.0f);
	Animation *testAnim2 = new Vec2Lerp(&testRef, Vec2(2.0f, 1.0f), Vec2(0.0f, 1.0f), 4900.0f);
	AnimationServer::getInstance()->registerAnimation(testAnim);	
	AnimationServer::getInstance()->registerAnimation(testAnim2);	
}

void timerTest(int argMSecPeriod)
{
	Timer timer(argMSecPeriod);
	for (int i = 0; i < 10; i++)
	{
		timer.start();
		timer.idle();
	}
}

}

int main(int argc, char **argv)
{

	Test::animationTest();
	//Test::displayTest(argc, argv);
	//Test::timerTest(atoi(argv[1]));

	while(1);
	
	std::cout << "\nfin.\n";
	return 0;
}
