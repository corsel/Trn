#include "background.h"

//Layer class
Layer::Layer(float argDistance /* = LAYER_DEFAULT_DISTANCE */)
: distance(argDistance)
{
	Vec2Lerp *testAnim = new Vec2Lerp(&position, Vec2(0.0f, 0.0f), Vec2(0.5f, 0.3f), 9999.0f);
	AnimationServer::getInstance()->registerAnimation(testAnim);
}
void Layer::render(float argOffset)
{
	glPushMatrix();
	glTranslatef(argOffset / distance, 0.0f, 0.0f);
	glTranslatef(position.x, position.y, 0.0f);
	glBegin(GL_QUADS);
	glColor4f(color.red, color.green, color.blue, color.alpha);
	glVertex2f(-0.3f, -0.3f);
	glVertex2f(0.3f, -0.3f);
	glVertex2f(0.3f, 0.3f);
	glVertex2f(-0.3f, 0.3f);
	glEnd();
	glPopMatrix();
}
void Layer::setColor(ColorRGBA argColor /*=ColorRGBA(0.2f, 0.2f, 0.2f, 1.0f)*/) //temp
{
	color = argColor;
}
void Layer::setPosition(Vec2 argPosition /*=Vec2()*/)
{
	position = argPosition;
}

//Background class
Background::Background()
: currentOffset(0.0f)
{
	layerVector.push_back(new Layer(10));
	layerVector[0]->setColor(ColorRGBA(0.5f, 0.2f, 0.2f, 1.0f));
	layerVector[0]->setPosition(Vec2(0.0f, 0.2f));
}
void Background::update()
{
	//currentOffset += 0.01f;
	for (int i = 0; i < layerVector.size(); i++)
	{
		layerVector[i]->render(0.0f);
	}
}
