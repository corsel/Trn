#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <iostream>
#include <vector>
#include <sys/time.h>
#include <pthread.h>
#include "utils.h"

class Animation; //forward declaration

class Timer
{
private:
	long prevSec;
	long prevUsec;
	int mSecPeriod;
	
public:
	Timer(int argMSecPeriod = (int)(1000.0f / 30.0f));
	void start(void);
	void idle(void);
};

class AnimationServer //singleton
{
private:
	pthread_t handle;
	bool killFlag;
	Timer *timer;
	const int stepSize;
	
	static std::vector<Animation*> animVector;
	
	static AnimationServer *instance;
	
	AnimationServer(void);
	static void *threadLoop(void*);

public:
	~AnimationServer(void);
	static AnimationServer *getInstance(void);
	void registerAnimation(Animation *argAnimation);
	int getStepSize(void);
};

class Animation //abstract
{
protected:
	float lifetime;
	float currentTime;
	bool isDead;
	int iteration;
	std::vector<Animation*> next;
	//Animation *next = NULL;
	
	void registerNext(Animation *argNext);
	
public:
	Animation(float argLifetime, Animation *argPrevious = NULL);
	virtual ~Animation(void) = 0;
	virtual void deferredInit(void *argDeferredInitParams) = 0;
	virtual void step(void) = 0;
	virtual bool getIsDead(void);
};

class Vec2Lerp : public Animation
{
private:
	Vec2 start, end;
	Vec2 stepDelta;
	int numIterations;
	Vec2 *ref;
	
public:
	Vec2Lerp(Vec2 *argRef, Vec2 argStart, Vec2 argEnd, float argLifetime, Animation *argPrevious = NULL);
	Vec2Lerp(Vec2 *argRef, Vec2 argRelEnd, float argLifetime, Animation *argPrevious = NULL);
	~Vec2Lerp(void);
	void deferredInit(void *argDeferredInitParams); //virtual implementation
	void step(void); //virtual implementation
};

class ColorAnim : public Animation
{
private:
	ColorRGBA start, end;
	ColorRGBA stepDelta;
	int numIterations;
	ColorRGBA *ref;
	
public:
	ColorAnim(ColorRGBA *argRef, ColorRGBA argEnd, float argLifetime, Animation *argPrevious = NULL);
	~ColorAnim(void);
	void deferredInit(void* argDeferredInitParams); //virtual implementation
	void step(void); //virtual implementation
};

#endif //ANIMATION_H_INCLUDED
