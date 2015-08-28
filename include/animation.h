#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <iostream>
#include <vector>
#include <pthread.h>
#include "utils.h"

template <typename T>
class Animation
{
protected:
	float lifeTime;
	float currentTime;
	bool isDead;
	
	T startVal, endVal;
	T *ref;
	
public:
	Animation(T *argRef, T argStart, T argEnd, float argLifeTime = 0.0f);
	virtual ~Animation(void);
	virtual void step(float argStepSize) = 0;
	virtual bool getIsDead(void);
};

class AnimationServer //singleton
{
private:
	pthread_t handle;
	bool killFlag;
	
	static std::vector<Animation<Vec2>*> vec2AnimVector;
	static std::vector<Animation<float>*> floatAnimVector;
	
	static AnimationServer *instance;
	
	AnimationServer(void);
	static void *threadLoop(void*);

public:
	~AnimationServer(void);
	static AnimationServer *getInstance(void);
	void registerAnimation(Animation<Vec2> *argAnimation);
	void registerAnimation(Animation<float> *argAnimation);
};

class Vec2Lerp : public Animation<Vec2>
{
private:
	
public:
	Vec2Lerp(Vec2 *argRef, Vec2 argStart, Vec2 argEnd, float argLifeTime = 0.0f);
	~Vec2Lerp(void);
	void step(float argStepSize); //virtual implementation
};

class ColorLerp : public Animation<ColorRGBA>
{
private:

public:
	ColorLerp(ColorRGBA *argColor, ColorRGBA argStart, ColorRGBA argEnd, float argLifeTime = 0.0f);
	~ColorLerp(void);
	void step(float argStepSize); //virtual implementation
};

#endif //ANIMATION_H_INCLUDED

