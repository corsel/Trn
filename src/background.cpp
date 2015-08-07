#include "background.h"

//Layer class
Layer::Layer(float argDistance /* = LAYER_DEFAULT_DISTANCE */)
: distance(argDistance)
{	
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
	layerVector.push_back(new Layer(20));
	layerVector[1]->setColor(ColorRGBA(0.2f, 0.6f, 0.6f, 1.0f));
	layerVector[1]->setPosition(Vec2(0.0f, -0.1f));
}
void Background::update()
{
	currentOffset += 0.01f;
	for (int i = 0; i < layerVector.size(); i++)
	{
		layerVector[i]->render(currentOffset);
	}
}
