#include "dialog-box.h"

//Bubble Class
Bubble::Bubble() {}
Bubble::Bubble(Vec2 argSize, Vec2 argPosn, float argFilletSize)
: halfSize(argSize / 2.0f), posn(argPosn), filletSize(argFilletSize) {}
void Bubble::render()
{
	//if (animation != NULL) animation->step();
	glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(posn.x - halfSize.x, posn.y - halfSize.y);
	glVertex2f(posn.x + halfSize.x, posn.y - halfSize.y);
	glVertex2f(posn.x + halfSize.x, posn.y + halfSize.y);
	glVertex2f(posn.x - halfSize.x, posn.y + halfSize.y);
	glEnd();
}

//BubbleContainer class
BubbleContainer *BubbleContainer::instance = NULL;
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
