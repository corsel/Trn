#ifndef DIALOG_BOX_H_INCLUDED
#define DIALOG_BOX_H_INCLUDED

#include <vector>
#include <GL/freeglut.h>
#include "utils.h"

//Bubble class
class Bubble
{
private:
	Vec2 halfSize;
	float filletSize;
	
public:
	Bubble(void);
	Bubble(Vec2 argSize, float argFilletSize);
	void render(void);
};

//BubbleContainer class
class BubbleContainer //singleton
{
private:
	std::vector<Bubble*> bubbleVector;
	BubbleContainer *instance = NULL;
	BubbleContainer(void);
	
public:
	BubbleContainer *getInstance(void);
	void appendBubble(Bubble *argBubble);
	void render(void);
};

#endif //DIALOG_BOX_H_INCLUDED

