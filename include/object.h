#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <iostream>
#include <GL/freeglut.h>
#include "utils.h"

class Object //abstract
{
private:
public:
	Object(void);
	~Object(void);
	virtual void update(void) = 0;
};

class Box : public Object
{
//private:
public:
	Vec2 size;
	Vec2 posn;
	ColorRGBA color;
public:
	Box(void);
	Box(Vec2 argPosn, Vec2 argSize, ColorRGBA argColor);
	~Box(void);
	void update(void);
};

#endif //OBJECT_H_INCLUDED
