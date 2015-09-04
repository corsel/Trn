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
	std::cout << "Debug - AnimationServer: threadLoop started.\n";
	while(AnimationServer::getInstance()->killFlag)
	{
		instance->timer->start();
		for (int i = 0; i < animVector.size(); i++)
		{
			if (animVector[i]->getIsDead())
			{
				std::cout << "Debug - AnimationServer: Animation killed: " << animVector[i] << std::endl;
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
void Animation::setNext(Animation *argNext)
{
	next = argNext;
}
Animation::Animation(float argLifetime, Animation *argPrevious)
: isDead(false), lifetime(argLifetime), iteration(0)
{
	if (argPrevious != NULL)
		argPrevious->setNext(this);
}
Animation::~Animation()
{
	if (next != NULL)
		AnimationServer::getInstance()->registerAnimation(next);
	std::cout << "Debug - Animation: Destructor called.\n";
}
bool Animation::getIsDead() { return isDead; }

//Vec2Lerp class
Vec2Lerp::Vec2Lerp(Vec2 *argRef, Vec2 argStart, Vec2 argEnd, float argLifetime, Animation *argPrevious)
: Animation(argLifetime, argPrevious), ref(argRef), start(argStart), end(argEnd) 
{
	numIterations = lifetime / (float)AnimationServer::getInstance()->getStepSize();
	stepDelta = (end - start) / numIterations;
	*ref = start;
}
Vec2Lerp::Vec2Lerp(Vec2 *argRef, Vec2 argRelEnd, float argLifetime, Animation *argPrevious)
: Animation(argLifetime, argPrevious), ref(argRef), start(*ref), end(start + argRelEnd) 
{
	numIterations = lifetime / (float)AnimationServer::getInstance()->getStepSize();
	stepDelta = (end - start) / numIterations;
	*ref = start;
}
Vec2Lerp::~Vec2Lerp()
{
	std::cout << "Debug - Vec2Lerp: Destructor called.\n";
}
void Vec2Lerp::step() //virtual implementation
{
	std::cout << "Debug - Vec2Lerp: \n\tanimation: " << this << "\tstep: " << iteration++ << "\tvalue: <" << ref->x << ", " << ref->y << ">\n";
	*ref += stepDelta;
	if (iteration >= numIterations)
	{
		*ref = end;
		isDead = true;
		std::cout << "Debug - Vec2Lerp: killing animation " << this << std::endl;
	}
}
