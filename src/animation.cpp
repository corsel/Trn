#include "animation.h"

//Timer class
Timer::Timer(int argMSecPeriod)
: mSecPeriod(argMSecPeriod) 
{
	std::cout << "Debug - Timer: Constructor called with period " << mSecPeriod << std::endl;
}
void Timer::start()
{
	timeval tmpTime;
	gettimeofday(&tmpTime, NULL);
	prevSec = tmpTime.tv_sec;
	prevUsec = tmpTime.tv_usec;
}
void Timer::idle()
{
	timeval tmpTime;
	gettimeofday(&tmpTime, NULL);
	int tmpDelta = (tmpTime.tv_sec - prevSec) * 1000 + (tmpTime.tv_usec - prevUsec) / 1000;
	if (tmpDelta > mSecPeriod)
	{
		 std::cout << "Debug - Timer: Timer has lagged. delta time: " << tmpDelta << " expected period: " << mSecPeriod << std::endl;
		 prevSec = tmpTime.tv_sec;
		 prevUsec = tmpTime.tv_usec;
		 return;
	}
	do
	{
		gettimeofday(&tmpTime, NULL);
		tmpDelta = (tmpTime.tv_sec - prevSec) * 1000 + (tmpTime.tv_usec - prevUsec) / 1000;
		if (tmpDelta >= mSecPeriod) break;
	} while (true);
}

//AnimationServer class
std::vector<Animation*> AnimationServer::animVector;
AnimationServer *AnimationServer::instance = NULL;
AnimationServer::AnimationServer()
: killFlag(true), stepSize((int)(1000.0f / 30.0f))
{
	timer = new Timer(stepSize);
	pthread_create(&handle, NULL, threadLoop, NULL);
}
AnimationServer::~AnimationServer()
{
	delete timer;
	pthread_exit(NULL);
}
void *AnimationServer::threadLoop(void *argArgs) //static
{
	std::cout << "Debug - AnimationServer::threadLoop: Called.\n";
	while(AnimationServer::getInstance()->killFlag)
	{
		instance->timer->start();
		for (int i = 0; i < animVector.size(); i++)
		{
			if (animVector[i]->getIsDead())
			{
				std::cout << "Debug - AnimationServer::threadLoop: Animation killed: " << animVector[i] << std::endl;
				delete animVector[i];
				animVector.erase(animVector.begin() + i);
				continue;
			}
			animVector[i]->step();
		}
		instance->timer->idle();
	}
}
AnimationServer *AnimationServer::getInstance() //static
{
	if (instance == NULL)
	{
		instance = new AnimationServer();
	}
	return instance;
}
void AnimationServer::registerAnimation(Animation *argAnimation) 
{
	animVector.push_back(argAnimation);
}
int AnimationServer::getStepSize() { return stepSize; }

//Animation class
void Animation::registerNext(Animation *argNext) //private
{
	next.push_back(argNext);
}
Animation::Animation(float argLifetime, Animation *argPrevious)
: isDead(false), lifetime(argLifetime), iteration(0)
{
	if (argPrevious != NULL)
	{
		argPrevious->registerNext(this);
	}
}
Animation::~Animation()
{
	for (int i = 0; i < next.size(); i++)
		AnimationServer::getInstance()->registerAnimation(next[i]);
	std::cout << "Debug - Animation::~Animation: Destructor called.\n";
}

bool Animation::getIsDead() { return isDead; }

//Vec2Lerp class
Vec2Lerp::Vec2Lerp(Vec2 *argRef, Vec2 argStart, Vec2 argEnd, float argLifetime, Animation *argPrevious)
: Animation(argLifetime, argPrevious), ref(argRef), start(argStart), end(argEnd) 
{
	if (argPrevious != NULL)
		return;
	numIterations = lifetime / (float)AnimationServer::getInstance()->getStepSize();
	stepDelta = (end - start) / numIterations;
	*ref = start;
}
Vec2Lerp::Vec2Lerp(Vec2 *argRef, Vec2 argRelEnd, float argLifetime, Animation *argPrevious)
: Animation(argLifetime, argPrevious), ref(argRef), end(start + argRelEnd) 
{
	if (argPrevious != NULL)
		return;
	numIterations = lifetime / (float)AnimationServer::getInstance()->getStepSize();
	stepDelta = (end - start) / numIterations;
}
Vec2Lerp::~Vec2Lerp()
{
	for (int i = 0; i < next.size(); i++)
		next[i]->deferredInit((void*)ref);
	std::cout << "Debug - Vec2Lerp::~Vec2Lerp: Destructor called.\n";
}
void Vec2Lerp::deferredInit(void *argDeferredInitParams) //virtual implementation
{
	Vec2 *deferredRef = (Vec2*)argDeferredInitParams;
	end = end - start + *deferredRef;
	start = *deferredRef;
	numIterations = lifetime / (float)AnimationServer::getInstance()->getStepSize();
	stepDelta = (end - start) / numIterations;
}
void Vec2Lerp::step() //virtual implementation
{
	//std::cout << "Debug - Vec2Lerp::step: \n\tanimation: " << this << "\tstep: " << iteration << "\tvalue: <" << ref->x << ", " << ref->y << ">\n";
	*ref += stepDelta;
	if (iteration >= numIterations)
	{
		*ref = end;
		isDead = true;
		std::cout << "Debug - Vec2Lerp::step: killing animation " << this << std::endl;
	}
	iteration++;
}

//ColorAnim class
ColorAnim::ColorAnim(ColorRGBA *argRef, ColorRGBA argEnd, float argLifetime, Animation *argPrevious)
: Animation(argLifetime, argPrevious), ref(argRef), end(argEnd)
{
	if (argPrevious != NULL)
		return;
	numIterations = lifetime / (float)AnimationServer::getInstance()->getStepSize();
	stepDelta = (end - *ref) / numIterations;
}
ColorAnim::~ColorAnim()
{
	for (int i = 0; i < next.size(); i++)
		next[i]->deferredInit(NULL);
	std::cout << "Debug - ColorAnim::~ColorAnim: Destructor called.\n";
}
void ColorAnim::deferredInit(void* argDeferredInitParams) //virtual implementation
{
	numIterations = lifetime / (float)AnimationServer::getInstance()->getStepSize();
	stepDelta = (end - *ref) / numIterations;
}
void ColorAnim::step(void) //virtual implementation
{
	//std::cout << "Debug - ColorAnim::step: \n\tanimation: " << this << "\tstep: " << iteration << "\tvalue: <" << ref->red << ", " << ref->green << ", " << ref->blue << ", " << ref->alpha << ">\n";
	*ref += stepDelta;
	if (iteration >= numIterations)
	{
		*ref = end;
		isDead = true;
		std::cout << "Debug - ColorAnim::step: killing animation " << this << std::endl;
	}
	iteration++;
}
