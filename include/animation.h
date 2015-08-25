#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <iostream>
#include "utils.h"

template <typename T>
class Animation
{
protected:
	float lifeTime;
	float currentTime;
	bool isAlive;
	
	T startVal, endVal;
	T *ref;
	
public:
	Animation(T *argRef, T argStart, T argEnd, float argLifeTime = 0.0f);
	virtual void step(float argStepSize) = 0;
	virtual bool getIsAlive(void);
};

class Vec2Lerp : public Animation<Vec2>
{
private:
	
public:
	Vec2Lerp(Vec2 *argRef, Vec2 argStart, Vec2 argEnd, float argLifeTime = 0.0f);
	void step(float argStepSize); //virtual implementation
};

#endif //ANIMATION_H_INCLUDED

