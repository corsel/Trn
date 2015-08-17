#include "dialog-box.h"

//Bubble Class
Bubble::Bubble() {}
Bubble::Bubble(Vec2 argSize, float argFilletSize)
: halfSize(argSize / 2.0f), filletSize(argFilletSize) {}
void Bubble::render()
{
	glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(-halfSize.x, -halfSize.y);
	glVertex2f(halfSize.x, -halfSize.y);
	glVertex2f(halfSize.x, halfSize.y);
	glVertex2f(-halfSize.x, halfSize.y);
	glEnd();
}

//BubbleContainer class
BubbleContainer::BubbleContainer() {}
BubbleContainer *BubbleContainer::getInstance()
{
	if (instance == NULL)
		instance = new BubbleContainer();
	
	return instance;
}
void BubbleContainer::appendBubble(Bubble *argBubble)
{
	bubbleVector.push_back(argBubble);
}
void BubbleContainer::render()
{
	for (int i = 0; i < bubbleVector.size(); i++)
	{
		bubbleVector[i]->render();
	}
}
