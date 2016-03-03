#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include "glut-functions.h"
#include "animation.h"

namespace Test
{

void displayTest(int argc, char **argv)
{
	TrnGlutFunctions::init(&argc, argv);
	activeLevel = new Level();
	glutMainLoop();
	//parseXml("data/test-file");
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

void animatedObjectTest(int argc, char **argv)
{
	TrnGlutFunctions::init(&argc, argv);
	TextureServer::getInstance();
	activeLevel = new Level();
	Box *box = new Box(Vec2(-0.1f, 0.1f), Vec2(0.3f, 0.2f), ColorRGBA(0.2f, 0.6f, 0.3f, 1.0f));
	activeLevel->pushObject(box);
	Vec2Lerp *boxAnim = new Vec2Lerp(&box->posn, Vec2(-0.1f, 0.1f), Vec2(1.0f, 1.0f), 4000.0f);
	Vec2Lerp *boxAnim2 = new Vec2Lerp(&box->posn, Vec2(1.0f, 1.0f), Vec2(0.0f, -1.0f), 5000.0f, boxAnim);
	ColorAnim *colorAnim = new ColorAnim(&box->color, ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f), 2000.0f, boxAnim2);
	Vec2Lerp *boxAnim3 = new Vec2Lerp(&box->posn, Vec2(-1.0f, 1.0f), 3000.0f, boxAnim2);
	AnimationServer::getInstance()->registerAnimation(boxAnim);
	glutMainLoop();
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

void textureTest(const char *argTextureFile)
{
	TextureServer::getInstance()->generateTexture(argTextureFile, 0, 100, 100);
}
}

int main(int argc, char **argv)
{

	//Test::animationTest();
	//Test::displayTest(argc, argv);
	//Test::timerTest(atoi(argv[1]));
	Test::textureTest("data/test_texture_0.bmp");
	TextureServer::getInstance()->bindTexture(0);
	Test::animatedObjectTest(argc, argv);
	
	std::cout << "\nfin.\n";
	while(1);
	return 0;
}
