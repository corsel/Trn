#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#define LAYER_DEFAULT_DISTANCE 10.0f

#include <vector>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "utils.h"
#include "timer.h"

class Layer
{
private:
	float distance;
	Vec2 position;
	ColorRGBA color; //temp
	
public:
	Layer(float argDistance = LAYER_DEFAULT_DISTANCE);
	void render(float argOffset);
	void setColor(ColorRGBA argColor = ColorRGBA(0.2f, 0.2f, 0.2f, 1.0f)); //temp
	void setPosition(Vec2 argPosition = Vec2());
};

class Background
{
private:
	std::vector<Layer*> layerVector;
	Timer *timer;
	float currentOffset;
	
public:
	Background(void);
	void update(void);
};

#endif //BACKGROUND_H_INCLUDED

