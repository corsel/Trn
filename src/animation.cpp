#include "animation.h"

//Timer class
Timer::Timer(int argMSecPeriod)
: mSecPeriod(argMSecPeriod) {}
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
	std::cout << "Debug - Timer: Timer step, delta time: " << tmpDelta << std::endl;
}

//AnimationServer class
std::vector<Animation*> AnimationServer::animVector;
AnimationServer *AnimationServer::instance = NULL;
AnimationServer::AnimationServer()
: killFlag(true)
{
	pthread_create(&handle, NULL, threadLoop, NULL);
}
AnimationServer::~AnimationServer()
{
	pthread_exit(NULL);
}
void *AnimationServer::threadLoop(void *argArgs) //static
{
	while(AnimationServer::getInstance()->killFlag)
	{
		instance->timer.start();
		for (int i = 0; i < animVector.size(); i++)
		{
			if (animVector[i]->getIsDead())
			{
				std::cout << "Debug - AnimationServer: Animation killed.\n";
				delete animVector[i];
				animVector.erase(animVector.begin() + i);
				continue;
			}
			animVector[i]->step();
		}
		instance->timer.idle();
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

//Animation class
void Animation::setNext(Animation *argNext)
{
	next = argNext;
}
Animation::Animation(float argLifetime, Animation *argPrevious)
: isDead(false), lifetime(argLifetime)
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
: Animation(argLifetime, argPrevious), ref(argRef), start(argStart), end(argEnd) {}
Vec2Lerp::Vec2Lerp(Vec2 *argRef, Vec2 argRelEnd, float argLifetime, Animation *argPrevious)
: Animation(argLifetime, argPrevious), ref(argRef), start(*ref), end(start + argRelEnd) {}
Vec2Lerp::~Vec2Lerp()
{
	std::cout << "Debug - Vec2Lerp: Destructor called.\n";
}
void Vec2Lerp::step() //virtual implementation
{
/*
	static int iteration = 0; //debug
	currentTime += stepSize;
	if (currentTime >= lifeTime && lifeTime != 0.0f)
	{
		*ref = endVal;
		std::cout << "Debug - Vec2Lerp: Animation is finished.\n";
		isDead = true;
		return;
	}
		*ref = startVal + (endVal - startVal) * (currentTime / lifeTime);
		std::cout << "Debug - Vec2Lerp: New step values are;\n\titeration: " << iteration++ << "\tcurrentTime: " << currentTime << "\tvalue: <" << ref->x << ", " << ref->y << ">\n";
*/
}
