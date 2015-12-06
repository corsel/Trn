#ifndef DIALOG_BOX_H_INCLUDED
#define DIALOG_BOX_H_INCLUDED

#include <vector>
#include <GL/freeglut.h>
#include "animation.h"
#include "utils.h"

//Bubble class
class Bubble
{
private:
	Vec2 posn;
	Vec2 halfSize;
	float filletSize;
	Vec2Lerp *animation = NULL;
	
public:
	Bubble(void);
	Bubble(Vec2 argSize, Vec2 argPosn = Vec2(0.0f, 0.0f), float argFilletSize = 0.0f);
	void render(void);
};

//BubbleContainer class
class BubbleContainer //singleton
{
private:
	std::vector<Bubble*> bubbleVector;
	static BubbleContainer *instance;
	BubbleContainer(void);
	
public:
	BubbleContainer *getInstance(void);
	void appendBubble(Bubble *argBubble);
	void render(void);
};

#endif //DIALOG_BOX_H_INCLUDED

